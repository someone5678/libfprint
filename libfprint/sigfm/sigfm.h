// SIGFM algorithm for libfprint

// Copyright (C) 2022 Matthieu CHARETTE <matthieu.charette@gmail.com>
// Copyright (c) 2022 Natasha England-Elbro <natasha@natashaee.me>
// Copyright (c) 2022 Timur Mangliev <tigrmango@gmail.com>
//
// SPDX-License-Identifier: LGPL-2.1-or-later
//

#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef unsigned char SigfmPix;
/**
 * @brief Contains information used by the sigfm algorithm for matching
 * @details Get one from sigfm_extract() and make sure to clean it up with sigfm_free_info()
 * @struct SigfmImgInfo
 */
typedef struct SigfmImgInfo SigfmImgInfo;

/**
 * @brief Extracts information from an image for later use sigfm_match_score
 *
 * @param pix Pixels of the image must be width * height in length
 * @param width Width of the image
 * @param height Height of the image
 * @return SigfmImgInfo* Info that can be used with the API
 */
SigfmImgInfo* sigfm_extract(const SigfmPix* pix, int width, int height);

/**
 * @brief Destroy an SigfmImgInfo
 * @warning Call this instead of free() or you will get UB!
 * @param info SigfmImgInfo to destroy
 */
void sigfm_free_info(SigfmImgInfo* info);

/**
 * @brief Score how closely a frame matches another
 *
 * @param frame Print to be checked
 * @param enrolled Canonical print to verify against
 * @return int Score of how closely they match, values <0 indicate error, 0 means always reject
 */
int sigfm_match_score(SigfmImgInfo* frame, SigfmImgInfo* enrolled);

/**
 * @brief Serialize an image info for storage
 *
 * @param info SigfmImgInfo to store
 * @param outlen output: Length of the returned byte array
 * @return unsigned* char byte array for storage, should be free'd by the callee
 */
unsigned char* sigfm_serialize_binary(SigfmImgInfo* info, int* outlen);
/**
 * @brief Deserialize an SigfmImgInfo from storage
 *
 * @param bytes Byte array to deserialize from
 * @param len Length of the byte array
 * @return SigfmImgInfo* Deserialized info, or NULL if deserialization failed
 */
SigfmImgInfo* sigfm_deserialize_binary(const unsigned char* bytes, int len);

/**
 * @brief Keypoints for an image. Low keypoints generally means the image is
 * low quality for matching
 *
 * @param info
 * @return int
 */

int sigfm_keypoints_count(SigfmImgInfo* info);

/**
 * @brief Copy an SigfmImgInfo
 *
 * @param info Source of copy
 * @return SigfmImgInfo* Newly allocated and copied version of info
 */
SigfmImgInfo* sigfm_copy_info(SigfmImgInfo* info);

#ifdef __cplusplus
}
#endif
