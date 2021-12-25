# Padstack (`*.pad`)

Looks like the file is mostly structured as a list of identifiers (increased one by one) with its trailing information. The information itself is then zero padded to 4 byte boundaries.

## Automation

`Padstack Editor` allows XML import/export of the padstack as a `*.pxml` file.

It's possible to record scripts (`*.scr`) for automated file generation.

## Temporary ZIP File while Saving Padstacks

When saving a padstack `Padstack Editor` creates a temporary file like `%USERPROFILE%\AppData\Local\Temp\#Taaaaaa00765.tmp`. The file name will probably be slightly different as the name is always adjusted to prevent name collisions. Further, the number at the end of the name is the zero padded process ID (PID) of `Padstack Editor`, in this example `765`.

[Process Monitor](https://docs.microsoft.com/en-us/sysinternals/downloads/procmon) can be used to investigate operating system calls of `Padstack Editor`. It shows that `Padstack Editor` starts `cdsZip.exe` and writes the temporary file `#Taaaaaa00765.tmp`.

Because the `*.tmp` file is directly deleted after the `*.pad` file was written, it is not possible to view it directly. However, it's possible to recover it with e.g. [Recuva](https://www.ccleaner.com/recuva) directly after the write process.

Running the `file` command on the temporary shows us that it's actually a ZIP file what explains why `cdsZip.exe` was called.

```bash
file \#Taaaaaa00765.tmp
#Taaaaaa00765.tmp: Zip archive data, at least v2.0 to extract
```

Trying to open it with `Padstack Editor` after renaming it to `*.pad` results in the following error, that suggests that padstacks were saved as ZIP files in older file format versions.

```text
ERROR(SPMHOD-19): Padstack revision is too old to open directly, use dbdoctor to uprev it.
```

Using `allegro_uprev` on it might upgrade the file to the current file format version.

Though the file is recognized as a ZIP file it can not be opened directly as the last data block in the file does not contain any information but rather all `0`'s. We can still recover the incomplete file with the following command.

```bash
zip -FF \#Taaaaaa00765.tmp --out recovered_zip
# Confirm 'Is this a single-disk archive?' with 'Y'.
unzip recovered_zip.zip
```

Alternatively [ezyZip](https://www.ezyzip.com/unzip-files-online.html#) and [extract.me](https://extract.me/) are free online extractors that can cope with the incomplete ZIP archive.

Taking a look at the extracted file `#Taaaaaa00765.tmp` we see that it's a [JSON](https://en.wikipedia.org/wiki/JSON) file containing padstack information in a human-readable way.

Note that the JSON implementation has some flaws. The following simplified example shows the issue. Observe that property `subclass_name` is assigned a string followed by a comma. This comma must only be used when there is some data following. In this case it's a syntax error that a few JSON parsers struggle with. Either find one, that accepts this comma or preprocess the JSON first and remove illegal commas.

```JSON
"padDesign" : {
	"pad" : [
	{
		"shape" : "Circle",
		"subclass_name" : "BEGIN LAYER",
	}
	]
}
```

## File Structure

Previously we saw that `Padstack Editor` saves some ZIP file before the `*.pad` file is generated. Actually the ZIP file is stored inside the binary `*.pad` file. Fortunately the temporary ZIP file is just incomplete and the all `0` block at the end of the archive is filled with legit information now. This means we can extract the ZIP from the `*.pad` by using the following command, where `skip` specifies the hexadecimal offset and `count` the hexadecimal byte length of the ZIP file. The beginning of the ZIP can be easily found by its [magic byte `PK\x03\x04`](https://en.wikipedia.org/wiki/ZIP_(file_format)) sequence.

```bash
dd if=my_pad.pad bs=1 status=none skip=$((0xabc)) count=$((0x123)) of=my_pad.zip
```

The ZIP can now be opened with any standard archive viewer and the JSON file can be extracted. It makes probably sense to rename the extracted `#Taaaaaa00765.tmp` to `my_pad.json`.

The following regular expression will match the temporary files.

```text
#T[a-z]{6}\d{5}\.tmp
```

Note that the temporary ZIP file and the actual ZIP inside the `*.pad` have the exact same byte length.

Looks like the JSON files exist only in newer file format versions. However opening an old file with a "new" Allegro version will integrate the JSON into the file.
