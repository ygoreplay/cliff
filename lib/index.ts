import type { ReplayParseResult } from "./types";

const cliff = require("bindings")("cliff");

export function initialize(databasePath: string, scriptsDirectoryPath: string) {
    cliff.initialize(databasePath, scriptsDirectoryPath);
}
export function parse(replayFilePath: string): ReplayParseResult {
    return cliff.parse(replayFilePath);
}
