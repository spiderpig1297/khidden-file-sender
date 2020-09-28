/**
 * This file is part of the khidden-file-sender module (https://github.com/spiderpig1297/khidden-file-sender).
 * Copyright (c) 2015 Idan Ofek.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "../fs/file_info.h"

#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/mutex.h>

// mutex to avoid race-conditions while accessing the list.
extern struct mutex pending_files_to_be_sent_mutex;

// list of files to send
extern struct list_head pending_files_to_be_sent;

// register and unregister the char device.
int register_input_chrdev(const char* device_name);
void unregister_input_chrdev(int major_num, const char* device_name);
