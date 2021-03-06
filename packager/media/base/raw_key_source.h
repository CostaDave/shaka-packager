// Copyright 2016 Google Inc. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef PACKAGER_MEDIA_BASE_RAW_KEY_SOURCE_H_
#define PACKAGER_MEDIA_BASE_RAW_KEY_SOURCE_H_

#include <memory>
#include <string>
#include <vector>

#include "packager/media/base/key_source.h"
#include "packager/media/public/crypto_params.h"

namespace shaka {
namespace media {

// Unofficial fairplay system id extracted from
// https://forums.developer.apple.com/thread/6185.
const uint8_t kFairplaySystemId[] = {0x29, 0x70, 0x1F, 0xE4, 0x3C, 0xC7,
                                     0x4A, 0x34, 0x8C, 0x5B, 0xAE, 0x90,
                                     0xC7, 0x43, 0x9A, 0x47};

/// A key source that uses raw keys for encryption.
class RawKeySource : public KeySource {
 public:
  ~RawKeySource() override;

  /// @name KeySource implementation overrides.
  /// @{
  Status FetchKeys(EmeInitDataType init_data_type,
                   const std::vector<uint8_t>& init_data) override;
  Status GetKey(const std::string& stream_label, EncryptionKey* key) override;
  Status GetKey(const std::vector<uint8_t>& key_id,
                EncryptionKey* key) override;
  Status GetCryptoPeriodKey(uint32_t crypto_period_index,
                            const std::string& stream_label,
                            EncryptionKey* key) override;
  /// @}

  /// Creates a new RawKeySource from the given data.  Returns null
  /// if the parameter is malformed.
  /// @param raw_key contains parameters to setup the key source.
  static std::unique_ptr<RawKeySource> Create(const RawKeyParams& raw_key,
                                              int protection_system_flags);

 protected:
  // Allow default constructor for mock key sources.
  RawKeySource();

 private:
  explicit RawKeySource(EncryptionKeyMap&& encryption_key_map,
                        int protection_systems_flags);
  RawKeySource(const RawKeySource&) = delete;
  RawKeySource& operator=(const RawKeySource&) = delete;

  EncryptionKeyMap encryption_key_map_;
};

}  // namespace media
}  // namespace shaka

#endif  // PACKAGER_MEDIA_BASE_RAW_KEY_SOURCE_H_
