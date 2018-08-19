# GlueUpdater
A simple cross-platform Qt-based updater software

GlueUpdater is an implementation of an auto-updating software to be used in Qt projects. It allows you to easily check for updates, download, and 'install' them. 

GlueUpdater parses JSON data to determine what to download for the particular OS, and where to download and install the files downloaded. The JSON file looks like the following:

```json
{
  "updates": {
    "operatingsystem": [
      {
        "operation": "remove",
        "file-location": "test.txt"
      }
    ],
    "linux": [
      {
        "operation": "remove",
        "file-location": "/home/ubuntu/test.txt"
      },
      {
        "operation": "add",
        "download-url": "http://example.com/file1.zip",
        "download-location": "/home/ubuntu/test1.zip",
        "extract-path": "/home/ubuntu/test1.zip"
      },
      {
        "operation": "update",
        "download-url": "http://example.com/file2.zip",
        "download-location": "/home/ubuntu/test2.zip",
        "extract-path": "/home/ubuntu/renamed.zip"
      }
    ]
  }
}
```
The MainWindow looks as follows:

![MainWindow](https://raw.githubusercontent.com/sanusbaum/GlueUpdater/master/screenshots/MainWindow.png)

The GlueUpdater window looks as follows:

![GlueUpdater](https://raw.githubusercontent.com/sanusbaum/GlueUpdater/master/screenshots/GlueUpdater.png)

And, the GlueUpdaterDialog looks as follows:

![GlueUpdaterDialog](https://raw.githubusercontent.com/sanusbaum/GlueUpdater/master/screenshots/GlueUpdaterDialog.png)
