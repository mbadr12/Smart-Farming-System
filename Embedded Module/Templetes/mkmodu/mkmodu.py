import os
import sys
from templates import Template


module_name = ""
def main():
    # Get the arguments passed to script
    module_name = sys.argv[1]
    layer_name = sys.argv[2]
    author_name = sys.argv[3]
    temps = Template(module_name, layer_name, author_name)

    # Create Director in the current path
    current_path = os.getcwd()
    os.mkdir(module_name)
    module_dir = current_path + f'/{module_name}/'

    # change to module_dir
    os.chdir(module_dir)
    current_path = os.getcwd()

    # create src and inc folders
    os.mkdir("Src")
    os.mkdir("Inc")

    # cd in Src
    os.chdir(f"{module_dir}/Src")

    # create program.c
    f = open(f"{temps.module_name}_Program.c", "w")
    f.write(temps.get_program_template())

    # cd in Inc
    os.chdir(f"{module_dir}/Inc")

    # 1. create interface.h
    f = open(f"{temps.module_name}_Interface.h", "w")
    f.write(temps.get_interface_template())
    
    # 2. create config.h
    f = open(f"{temps.module_name}_Config.h", "w")
    f.write(temps.get_config_template())

    # 3. create private.h
    f = open(f"{temps.module_name}_Private.h", "w")
    f.write(temps.get_private_template())

    # 4. create types.h
    f = open(f"{temps.module_name}_Types.h", "w")
    f.write(temps.get_types_template())

    f.close()




    


    # Get the path from which the script is run



    pass

main()
