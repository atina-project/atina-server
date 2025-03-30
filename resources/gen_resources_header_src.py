import json
import os
import sys

def main():
    header_output_dir = sys.argv[1]
    source_output_dir = sys.argv[2]

    with open("resource_en.json", 'r', encoding='utf-8') as rfile:
        en_data = json.load(rfile)

    with open("resource_zhCN.json", 'r', encoding='utf-8') as rfile:
        zhCN_data = json.load(rfile)

    resources_map_decls = ""
    resources_map_defs = ""

    for key, value in en_data.items():
        resources_map_decls += f"    extern std::unordered_map<std::string, std::unordered_map<std::string, std::string>> {key};\n"
        resources_map_defs += f"std::unordered_map<std::string, std::unordered_map<std::string, std::string>> atina::server::resources::{key} = {{\n"
        resources_map_defs += "    {\"en\", {\n"
        first_key = True
        for subkey, subvalue in value.items():
            if first_key:
                resources_map_defs += f"        {{\"{subkey}\", \"{subvalue}\"}}"
                first_key = False
            else:
                resources_map_defs += f",\n        {{\"{subkey}\", \"{subvalue}\"}}"
        resources_map_defs += "\n    }},\n"
        resources_map_defs += "    {\"zhCN\", {\n"
        first_key = True
        for subkey, subvalue in zhCN_data[key].items():
            if first_key:
                resources_map_defs += f"        {{\"{subkey}\", \"{subvalue}\"}}"
                first_key = False
            else:
                resources_map_defs += f",\n        {{\"{subkey}\", \"{subvalue}\"}}"
        resources_map_defs += "\n    }}\n"
        resources_map_defs += "};\n"

    with open("resources.h.in", 'r', encoding='utf-8') as rfile:
        header_template = rfile.read()

    with open("resources.cpp.in", 'r', encoding='utf-8') as rfile:
        source_template = rfile.read()

    header = header_template.replace("@INSERT_RESOURCES_MAP_DECLS@", resources_map_decls)
    source = source_template.replace("@INSERT_RESOURCES_MAP_DEFS@", resources_map_defs)

    if not os.path.exists(header_output_dir):
        os.makedirs(header_output_dir)

    if not os.path.exists(source_output_dir):
        os.makedirs(source_output_dir)

    with open(os.path.join(header_output_dir, "resources.h"), 'w', encoding='utf-8') as wfile:
        wfile.write(header)

    with open(os.path.join(source_output_dir, "resources.cpp"), 'w', encoding='utf-8') as wfile:
        wfile.write(source)

if __name__ == "__main__":
    main()
