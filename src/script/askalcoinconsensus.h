// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Askalcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ASKALCOIN_SCRIPT_ASKALCOINCONSENSUS_H
#define ASKALCOIN_SCRIPT_ASKALCOINCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_ASKALCOIN_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/askalcoin-config.h>
  #if defined(_WIN32)
    #if defined(HAVE_DLLEXPORT_ATTRIBUTE)
      #define EXPORT_SYMBOL __declspec(dllexport)
    #else
      #define EXPORT_SYMBOL
    #endif
  #elif defined(HAVE_DEFAULT_VISIBILITY_ATTRIBUTE)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBASKALCOINCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define ASKALCOINCONSENSUS_API_VER 1

typedef enum askalcoinconsensus_error_t
{
    askalcoinconsensus_ERR_OK = 0,
    askalcoinconsensus_ERR_TX_INDEX,
    askalcoinconsensus_ERR_TX_SIZE_MISMATCH,
    askalcoinconsensus_ERR_TX_DESERIALIZE,
    askalcoinconsensus_ERR_AMOUNT_REQUIRED,
    askalcoinconsensus_ERR_INVALID_FLAGS,
} askalcoinconsensus_error;

/** Script verification flags */
enum
{
    askalcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    askalcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    askalcoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    askalcoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    askalcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    askalcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    askalcoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    askalcoinconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = askalcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH | askalcoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               askalcoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | askalcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               askalcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | askalcoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int askalcoinconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, askalcoinconsensus_error* err);

EXPORT_SYMBOL int askalcoinconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, askalcoinconsensus_error* err);

EXPORT_SYMBOL unsigned int askalcoinconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // ASKALCOIN_SCRIPT_ASKALCOINCONSENSUS_H
