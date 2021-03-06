import "../GenericPlugin.qbs" as GenericPlugin

GenericPlugin {
    type: [ "dynamiclibrary", "installed_content" ]

    Depends { name: "artwork" }
    Depends { name: "attica" }
    Depends { name: "libarchive" }
    Depends { name: 'qt.declarative' }
    Depends { name: 'qt.opengl' }

    Group {
        fileTags: [ "artwork" ]
        artwork.basePath: "qml"
        prefix: "qml/plugman/"
        files: "**"
    }
}
