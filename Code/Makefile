#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := project_template
CFLAGS += -DICACHE_FLASH

my_all: main/html_page.h all

main/html_page.h: main/html_page.html
	./mktemplate.py main/html_page.html > main/html_page.h
    
include $(IDF_PATH)/make/project.mk

# vi: noet ts=8 sw=4
