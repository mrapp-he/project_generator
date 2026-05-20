
#ifndef DEFINES_HPP
# define DEFINES_HPP

# define MAIN "/templates/main.cpp.tpl"
# define MAKE "/templates/Makefile.tpl"
# define HEADER "/templates/main.hpp.tpl"
# define R_CLASS "/templates/class.cpp.tpl"
# define R_HEADER "/templates/class.hpp.tpl"
# define OCF_CLASS "/templates/class_ocf.cpp.tpl"
# define OCF_HEADER "/templates/class_ocf.hpp.tpl"
# define ERR_NO_ARGS "Program didn't receive any arguments, please try again! | (to see correct usage use --help)"
# define ERR_TOO_MANY_ARGS "Program received too many arguments, please try again! | (to see correct usage use --help)"
# define USAGE_NO_CLASS "Program Usage:\n\nProject with no Classes:\n./project_generator [folder_name]\n"
# define USAGE_CLASS "\nProject with one Class:\n./project_generator [folder_name] [flag] [Class] | (to see flags use --flags)\n"
# define USAGE_CLASSES "\nProject with Classes:\n./project_generator [folder_name] [flag] [\"Class1 Class2...\"] | (to see flags use --flags)"
# define FLAGS "Flags:\n--r - regular class\n--ofc - orthodox cannonical form"

#endif