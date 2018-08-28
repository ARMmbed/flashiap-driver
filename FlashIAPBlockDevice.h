/* mbed Microcontroller Library
 * Copyright (c) 2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MBED_FLASHIAP_BLOCK_DEVICE_H
#define MBED_FLASHIAP_BLOCK_DEVICE_H

#ifdef DEVICE_FLASH

#include "BlockDevice.h"
#include <mbed.h>

#ifndef MBED_CONF_FLASHIAP_BLOCK_DEVICE_BASE_ADDRESS
#error flashiap-block-device.base-address not set
#endif

#ifndef MBED_CONF_FLASHIAP_BLOCK_DEVICE_SIZE
#error flashiap-block-device.size not set
#endif

/** BlockDevice using the FlashIAP API
 *
 *  @code
 *  #include "mbed.h"
 *  #include "FlashIAPBlockDevice.h"
 *
 */
class FlashIAPBlockDevice : public BlockDevice {
public:
    /** Creates a FlashIAPBlockDevice, starting at the given address and
     *  with a certain size.
     *
     *  @param address  Starting address for the BlockDevice
     *  @param size     Maximum size allocated to this BlockDevice
     */
    FlashIAPBlockDevice(uint32_t address = MBED_CONF_FLASHIAP_BLOCK_DEVICE_BASE_ADDRESS,
                        uint32_t size = MBED_CONF_FLASHIAP_BLOCK_DEVICE_SIZE);

    /** Initialize a block device
     *
     *  @return         0 on success or a negative error code on failure
     */
    virtual int init();

    /** Deinitialize a block device
     *
     *  @return         0 on success or a negative error code on failure
     */
    virtual int deinit();

    /** Read blocks from a block device
     *
     *  @param buffer   Buffer to write blocks to
     *  @param addr     Address of block to begin reading from
     *  @param size     Size to read in bytes, must be a multiple of read block size
     *  @return         0 on success, negative error code on failure
     */
    virtual int read(void *buffer, bd_addr_t addr, bd_size_t size);

    /** Program blocks to a block device
     *
     *  The blocks must have been erased prior to being programmed
     *
     *  @param buffer   Buffer of data to write to blocks
     *  @param addr     Address of block to begin writing to
     *  @param size     Size to write in bytes, must be a multiple of program block size
     *  @return         0 on success, negative error code on failure
     */
    virtual int program(const void *buffer, bd_addr_t addr, bd_size_t size);

    /** Erase blocks on a block device
     *
     *  The state of an erased block is undefined until it has been programmed
     *
     *  @param addr     Address of block to begin erasing
     *  @param size     Size to erase in bytes, must be a multiple of erase block size
     *  @return         0 on success, negative error code on failure
     */
    virtual int erase(bd_addr_t addr, bd_size_t size);

    /** Get the size of a readable block
     *
     *  @return         Size of a readable block in bytes
     */
    virtual bd_size_t get_read_size() const;

    /** Get the size of a programable block
     *
     *  @return         Size of a programable block in bytes
     *  @note Must be a multiple of the read size
     */
    virtual bd_size_t get_program_size() const;

    /** Get the size of a eraseable block
     *
     *  @return         Size of a eraseable block in bytes
     *  @note Must be a multiple of the program size
     */
    virtual bd_size_t get_erase_size() const;

    /** Get the size of an erasable block given address
     *
     *  @param addr     Address within the erasable block
     *  @return         Size of an erasable block in bytes
     *  @note Must be a multiple of the program size
     */
    virtual bd_size_t get_erase_size(bd_addr_t addr) const;

    /** Get the total size of the underlying device
     *
     *  @return         Size of the underlying device in bytes
     */
    virtual bd_size_t size() const;

private:
    // Device configuration
    FlashIAP _flash;
    bd_addr_t _base;
    bd_size_t _size;
    bool _is_initialized;
    uint32_t _init_ref_count;
};

#endif /* DEVICE_FLASH */
#endif /* MBED_FLASHIAP_BLOCK_DEVICE_H */
