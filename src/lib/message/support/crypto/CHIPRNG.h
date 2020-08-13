/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2013-2017 Nest Labs, Inc.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *      This file provides secure random data functions for the CHIP layer.
 *      Functions in this file are platform specific and their various custom
 *      implementations can be enabled.
 *
 */

#ifndef CHIPRNG_H_
#define CHIPRNG_H_

#include "CHIPCrypto.h"

#if CHIP_CONFIG_USE_OPENSSL_ECC && !CHIP_WITH_OPENSSL
#error                                                                                                                             \
    "INVALID CHIP CONFIG: OpenSSL RNG implementation enabled but OpenSSL not available (CHIP_CONFIG_RNG_IMPLEMENTATION_OPENSSL == 1 && CHIP_WITH_OPENSSL == 0)."
#endif

namespace chip {
namespace Platform {
namespace Security {

extern "C" {

/**
 * This function is called by the CHIP layer to initialize random data source.
 * This function is platform specific and might be empty when no initialization of
 * random data source is required.
 *
 * @param[in]  entropyFunct        Pointer to a function that generates entropy to the random
 *                                 data generator. When entropy input is not required by the
 *                                 algorith this input can be NULL, which is the case when OpenSSL
 *                                 version of the random data generator is used.
 *
 * @param[in]  entropyLen          Specifies entropy size in bytes that should be generated by
 *                                 the entropy function when it is used.
 *
 * @param[in]  personalizationData Pointer to a memory buffer that stores personalization data
 *                                 input. This data input should be device specific and it
 *                                 helps to improve statistical properties of the random data.
 *
 * @param[in]  perDataLen          Specifies personalization data size in bytes.
 *
 * @retval  #CHIP_ERROR_INVALID_ARGUMENT  If an invalid argument was passed to this function.
 * @retval  #CHIP_NO_ERROR                On success.
 *
 */
extern CHIP_ERROR InitSecureRandomDataSource(chip::Crypto::EntropyFunct entropyFunct, uint16_t entropyLen,
                                             const uint8_t * personalizationData, uint16_t perDataLen);

/**
 * This function is called by the CHIP layer to generate random data.
 *
 * @param[in]  buf      Pointer to a memory buffer, where requested random data should
 *                      be stored.
 *
 * @param[in]  len      Specifies requested random data size in bytes.
 *
 * @retval  #CHIP_ERROR_DRBG_ENTROPY_SOURCE_FAILED  If entropy source fails to generate entropy
 *                                                   requested by the random data generator.
 * @retval  #CHIP_ERROR_RANDOM_DATA_UNAVAILABLE     If random data source fails to generate
 *                                                   random data.
 * @retval  #CHIP_ERROR_INCORRECT_STATE             If random data source is found in a wrong state.
 * @retval  #CHIP_NO_ERROR                          On success.
 *
 */
extern CHIP_ERROR GetSecureRandomData(uint8_t * buf, uint16_t len);

} /* end of extern "C" */

#if CHIP_CONFIG_DEV_RANDOM_DRBG_SEED

extern int GetDRBGSeedDevRandom(uint8_t * buf, size_t bufSize);

#endif // CHIP_CONFIG_DEV_RANDOM_ENTROPY_SOURCE

} // namespace Security
} // namespace Platform
} // namespace chip

#endif /* CHIPRNG_H_ */