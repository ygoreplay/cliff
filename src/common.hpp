#ifndef CLIFF_COMMON_HPP
#define CLIFF_COMMON_HPP

#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <napi.h>

#include "SQLiteCpp/SQLiteCpp.h"

#include "LzmaLib.h"

#include "ocgapi.h"
#include "mtrandom.h"

#undef max
#undef min

#include "nlohmann/json.hpp"

namespace fs = std::filesystem;

typedef uint8_t byte;

#include "card-manager.hpp"
#include "buffer-reader.hpp"
#include "file-utils.hpp"
#include "parse-result.hpp"
#include "replay.hpp"
#include "game.hpp"

#endif //CLIFF_COMMON_HPP