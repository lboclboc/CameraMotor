#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := project_template
CFLAGS += -DICACHE_FLASH

my_all: main/html_page.h all

main/html_page.h: main/html_page.html
	(echo 'static char html_page[] = "\'; sed -e 's/"/\\"/g' -e 's/$$/\\/' main/html_page.html; echo; echo '";') > $@
    
include $(IDF_PATH)/make/project.mk

# vi: noet ts=8 sw=4
