// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Californium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CALIFORNIUM_SCRIPT_CALIFORNIUMCONSENSUS_H
#define CALIFORNIUM_SCRIPT_CALIFORNIUMCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_CALIFORNIUM_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/californium-config.h>
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBCALIFORNIUMCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CALIFORNIUMCONSENSUS_API_VER 1

typedef enum californiumconsensus_error_t
{
    californiumconsensus_ERR_OK = 0,
    californiumconsensus_ERR_TX_INDEX,
    californiumconsensus_ERR_TX_SIZE_MISMATCH,
    californiumconsensus_ERR_TX_DESERIALIZE,
    californiumconsensus_ERR_AMOUNT_REQUIRED,
    californiumconsensus_ERR_INVALID_FLAGS,
} californiumconsensus_error;

/** Script verification flags */
enum
{
    californiumconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    californiumconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    californiumconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    californiumconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    californiumconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    californiumconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    californiumconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    californiumconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = californiumconsensus_SCRIPT_FLAGS_VERIFY_P2SH | californiumconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               californiumconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | californiumconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               californiumconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | californiumconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int californiumconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, californiumconsensus_error* err);

EXPORT_SYMBOL int californiumconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, californiumconsensus_error* err);

EXPORT_SYMBOL unsigned int californiumconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // CALIFORNIUM_SCRIPT_CALIFORNIUMCONSENSUS_H
