#include "utils.hpp"

std::unordered_map<std::string, std::string> get_env_vars(std::string path) {

    std::unordered_map<std::string, std::string> env_var;
    std::ifstream env_file(path);
    std::string line;

    while (getline(env_file, line)) {

        int delim_pos = line.find("=");
        std::string key = line.substr(0, delim_pos);
        std::string value = line.substr(delim_pos+1);

        env_var[key] = value;

    }

    return env_var;

}
