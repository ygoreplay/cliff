const cliff = require("bindings")("cliff");

export function initialize(databasePath: string, scriptsDirectoryPath: string) {
    cliff.initialize(databasePath, scriptsDirectoryPath);
}

export function parse(replayFilePath: string) {
    return cliff.parse(replayFilePath);
}