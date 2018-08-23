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
      },
      {
        "operation": "move",
        "file-location": "test.txt",
        "file-move-location": "test1.txt"
      },
      {
        "operation": "mkdir",
        "directory-location": "test"
      },
      {
        "operation": "change-log",
        "change-log": "These are the changes I implemented..."
      }
    ]
  }
}
```

The available operations are: "remove", "add", "update", "move", "mkdir", and "change-log".

  - For "remove" the additional information should be listed in "file-location".

  - For "add" the additional information should be listed in "download-url", "download-location", and "extract-path".

  - For "update" the additional information should be listed in "download-url", "download-location", and "extract-path".

  - For "move" the additional information should be listed in "file-location", and "file-move-location".

  - For "mkdir" the additional information should be listed in "directory-location".

  - For "change-log" the additional information should be listed in "change-log"

The MainWindow looks as follows:

![MainWindow](https://raw.githubusercontent.com/sanusbaum/GlueUpdater/master/screenshots/MainWindow.png)

The GlueUpdater window looks as follows:

![GlueUpdater](https://raw.githubusercontent.com/sanusbaum/GlueUpdater/master/screenshots/GlueUpdater.png)

And, the GlueUpdaterDialog looks as follows:

![GlueUpdaterDialog](https://raw.githubusercontent.com/sanusbaum/GlueUpdater/master/screenshots/GlueUpdaterDialog.png)
