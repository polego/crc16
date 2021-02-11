/*
 * crc_16.h
 *
 * All rights reserved, Copyright Ogelop AB
 *
 * Created on: Feb 11, 2021
 *     Author: Niclas Wahllöf
 *
 */

#ifndef SRC_CRC_16_H_
#define SRC_CRC_16_H_

#include <stddef.h>
#include <stdint.h>

// Provided services

extern uint16_t crc_16(char *input_str, size_t num_bytes);

#endif /* SRC_CRC_16_H_ */

