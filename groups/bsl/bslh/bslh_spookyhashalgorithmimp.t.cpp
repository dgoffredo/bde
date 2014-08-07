// bslh_spookyhashalgorithmimp.t.cpp                                  -*-C++-*-
#include <bslh_spookyhashalgorithmimp.h>

#include <bsls_assert.h>
#include <bsls_asserttest.h>
#include <bsls_bsltestutil.h>
#include <bsls_platform.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace BloombergLP;
using namespace bslh;


//=============================================================================
//                             TEST PLAN
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// [ 5] static void Hash128(*msg, len, *h1, *h2);
// [ 6] static uint64 Hash64(*message, length, seed);
// [ 6] static uint32 Hash32(*message, length, seed);
// [ 3] void Init(uint64 seed1, uint64 seed2);
// [ 4] void Update(const void *message, size_t length);
// [ 3] void Final(uint64 *hash1, uint64 *hash2);
// [ 2] SpookyHashAlgorithmImp()
// [ 2] SpookyHashAlgorithmImp(const SpookyHashAlgorithmImp)
// [ 2] ~SpookyHashAlgorithmImp()
// [ 2] SpookyHashAlgorithmImp& operator=(const SpookyHashAlgorithmImp&)
// ----------------------------------------------------------------------------
// [ 1] BREATHING TEST
// [ 7] USAGE EXAMPLE
//-----------------------------------------------------------------------------

// ============================================================================
//                      STANDARD BDE ASSERT TEST MACROS
// ----------------------------------------------------------------------------
// NOTE: THIS IS A LOW-LEVEL COMPONENT AND MAY NOT USE ANY C++ LIBRARY
// FUNCTIONS, INCLUDING IOSTREAMS.

namespace {

int testStatus = 0;

void aSsErT(bool b, const char *s, int i)
{
    if (b) {
        printf("Error " __FILE__ "(%d): %s    (failed)\n", i, s);
        if (testStatus >= 0 && testStatus <= 100) ++testStatus;
    }
}

}  // close unnamed namespace

//=============================================================================
//                       STANDARD BDE TEST DRIVER MACROS
//-----------------------------------------------------------------------------

#define ASSERT       BSLS_BSLTESTUTIL_ASSERT
#define LOOP_ASSERT  BSLS_BSLTESTUTIL_LOOP_ASSERT
#define LOOP0_ASSERT BSLS_BSLTESTUTIL_LOOP0_ASSERT
#define LOOP1_ASSERT BSLS_BSLTESTUTIL_LOOP1_ASSERT
#define LOOP2_ASSERT BSLS_BSLTESTUTIL_LOOP2_ASSERT
#define LOOP3_ASSERT BSLS_BSLTESTUTIL_LOOP3_ASSERT
#define LOOP4_ASSERT BSLS_BSLTESTUTIL_LOOP4_ASSERT
#define LOOP5_ASSERT BSLS_BSLTESTUTIL_LOOP5_ASSERT
#define LOOP6_ASSERT BSLS_BSLTESTUTIL_LOOP6_ASSERT
#define ASSERTV      BSLS_BSLTESTUTIL_ASSERTV

#define Q   BSLS_BSLTESTUTIL_Q   // Quote identifier literally.
#define P   BSLS_BSLTESTUTIL_P   // Print identifier and value.
#define P_  BSLS_BSLTESTUTIL_P_  // P(X) without '\n'.
#define T_  BSLS_BSLTESTUTIL_T_  // Print a tab (w/o newline).
#define L_  BSLS_BSLTESTUTIL_L_  // current Line number

// ============================================================================
//                  NEGATIVE-TEST MACRO ABBREVIATIONS
// ----------------------------------------------------------------------------

#define ASSERT_SAFE_PASS(EXPR) BSLS_ASSERTTEST_ASSERT_SAFE_PASS(EXPR)
#define ASSERT_SAFE_FAIL(EXPR) BSLS_ASSERTTEST_ASSERT_SAFE_FAIL(EXPR)
#define ASSERT_PASS(EXPR)      BSLS_ASSERTTEST_ASSERT_PASS(EXPR)
#define ASSERT_FAIL(EXPR)      BSLS_ASSERTTEST_ASSERT_FAIL(EXPR)
#define ASSERT_OPT_PASS(EXPR)  BSLS_ASSERTTEST_ASSERT_OPT_PASS(EXPR)
#define ASSERT_OPT_FAIL(EXPR)  BSLS_ASSERTTEST_ASSERT_OPT_FAIL(EXPR)

//=============================================================================
//                   GLOBAL TYPEDEFS AND DATA FOR TESTING
//-----------------------------------------------------------------------------

typedef SpookyHashAlgorithmImp Obj;
typedef SpookyHashAlgorithmImp::uint64 uint64;

static const struct {
    int                  d_line;
    const char           d_value [21];
    bsls::Types::Uint64  d_hash1;
    bsls::Types::Uint64  d_hash2;
} DATA[] = {
#ifdef BSLS_PLATFORM_IS_LITTLE_ENDIAN
//LINE         DATA                   HASH1               HASH2
 {L_,                    "1", 0x612d8c9b675009f2LL, 0xcd3314880c9a9aa0LL,},
 {L_,                   "12", 0xe967e8b6395e6782LL, 0xce5d87cde404a8d7LL,},
 {L_,                  "123", 0xcfa6ecd463cc4a83LL, 0x5775b241699a59a2LL,},
 {L_,                 "1234", 0xc0160cf616434e0fLL, 0xf74a249bc3eb094eLL,},
 {L_,                "12345", 0x3a85d1d65047e444LL, 0x61be6127e909350cLL,},
 {L_,               "123456", 0xd5cfafa3081a22e8LL, 0xede555af1cb9f339LL,},
 {L_,              "1234567", 0x83298ef41b0686a2LL, 0x481b12c0bbe69f3eLL,},
 {L_,             "12345678", 0x95523fb668af544dLL, 0x9ccccd0a86f1cb8eLL,},
 {L_,            "123456789", 0x0d7ef6cdd1e36f52LL, 0x67a5803f214892e0LL,},
 {L_,           "1234567890", 0x4ebaf9a6220603bfLL, 0x7e2b78b551260231LL,},
 {L_,          "12345678901", 0xc061aea37169d1c4LL, 0xf7fee6d149f2d44eLL,},
 {L_,         "123456789012", 0xd99d4151893fb02cLL, 0x80671ad783b63b82LL,},
 {L_,        "1234567890123", 0x7eb6309f17d458f7LL, 0x2d551c3efa5f681aLL,},
 {L_,       "12345678901234", 0xfb4d4ec8048c4a82LL, 0x711721576df73490LL,},
 {L_,      "123456789012345", 0xcbdf3e9e0b34e18eLL, 0x583b606b5af867b2LL,},
 {L_,     "1234567890123456", 0x8b075d4175f50658LL, 0x7591726bc5e46e48LL,},
 {L_,    "12345678901234567", 0xff5e9188d483d1b2LL, 0xaa41ee0595b4410aLL,},
 {L_,   "123456789012345678", 0xe0923d0da7fc6adeLL, 0x76b72d2f794115a5LL,},
 {L_,  "1234567890123456789", 0xe23d476408fb578eLL, 0xc75c131145990dc9LL,},
 {L_, "12345678901234567890", 0x6e621ce4363d6a05LL, 0x0d0dacb9301bababLL,},
#else
 //LINE         DATA                   HASH1               HASH2
 {L_,                    "1", 0x612d8c9b675009f2LL, 0xcd3314880c9a9aa0LL,},
 {L_,                   "12", 0xe967e8b6395e6782LL, 0xce5d87cde404a8d7LL,},
 {L_,                  "123", 0xcfa6ecd463cc4a83LL, 0x5775b241699a59a2LL,},
 {L_,                 "1234", 0x5cf924ef45f9d230LL, 0xceb1f0b41cb8347eLL,},
 {L_,                "12345", 0x7868854e01d25200LL, 0x5a05c0bda46e16f3LL,},
 {L_,               "123456", 0x3f2628ed9531e9e2LL, 0x51e9f1e709607593LL,},
 {L_,              "1234567", 0xe9068cb0e8324f6aLL, 0x4c578f47d96f0febLL,},
 {L_,             "12345678", 0xe3f15e6f1811bbceLL, 0x5a0ff1e9222f059dLL,},
 {L_,            "123456789", 0x485d93342e7ec4c3LL, 0xb79c7e8027bfa6f8LL,},
 {L_,           "1234567890", 0xaa2839c8deb77e93LL, 0x2a0e25297b071d45LL,},
 {L_,          "12345678901", 0x1e16e0179ee1a7f2LL, 0xf986d8175c510726LL,},
 {L_,         "123456789012", 0xb100680daac30142LL, 0x18a3ddfdbedc6e5dLL,},
 {L_,        "1234567890123", 0xc66a7648d4c3a0a4LL, 0x9957b1255feb3c81LL,},
 {L_,       "12345678901234", 0xea71b094ce76f5caLL, 0x79bb75c8cf3250fdLL,},
 {L_,      "123456789012345", 0x82f097ae5f44cb64LL, 0x67583e9aa71dafdbLL,},
 {L_,     "1234567890123456", 0x88de1445a9eaf46eLL, 0x9a1229f888cd48a5LL,},
 {L_,    "12345678901234567", 0x18d3932ab34d2abeLL, 0x8f6829e038462b0fLL,},
 {L_,   "123456789012345678", 0x4177ac8b3ddf6bbbLL, 0x1b1a4c3205eb81e5LL,},
 {L_,  "1234567890123456789", 0xf7385269c6e0c0bcLL, 0x8198aaf48b47a35bLL,},
 {L_, "12345678901234567890", 0x90e8d7464a51b42aLL, 0x5f9b9ced6c8dfc10LL,},
#endif
};
const int NUM_DATA = sizeof DATA / sizeof *DATA;

//=============================================================================
//                             USAGE EXAMPLE
//-----------------------------------------------------------------------------
///Usage
///-----
// This section illustrates intended usage of this component.
//
///Example: Creating 128-bit checksums
///- - - - - - - - - - - - - - - - - - 
// Suppose we have a library of 4 billion pieces of data and we want to store
// checksums for this data. For a 64-bit hash, there is a 35% chance of two of
// these checksums colliding (according to the approximation found here:
// http://en.wikipedia.org/wiki/Birthday_problem). We want to avoid checksum
// collision, so we will use the 128-bit hashing functionality provided by
// 'SpookyHashAlgorithmImp'.
//
// First, we will declare a class 'CheckedData' which will store some data as
// well as the checksum associated with it.
//..

class CheckedData {
    typedef bsls::Types::Uint64 uint64;
    size_t      d_length;
    const char *d_data;
    uint64      d_checksum1;
    uint64      d_checksum2;

  public:
    // Stores some data along with the associated checksum.
    CheckedData(const char *data, size_t length);
        // Creates an instance of this class with the specified 'length' bytes
        // of 'data'. Note that only a pointer to the data will be maintained,
        // it will not be copied.

    const char *GetData();
        // Return a pointer to the data being tracked by this class.

    bool IsDataValid();
        // Return true of the data stored in this class matches the stored
        // checksum and is considered valid.
};

//..
// Then, we will define the 'CheckedData' constructor. Here we will use
// 'SpookyHashImp' to calculate a 128-bit checksum.
//..

CheckedData::CheckedData(const char *data, size_t length) : d_data(data),
                                                            d_length(length),
                                                            d_checksum1(0),
                                                            d_checksum2(0) {
    SpookyHashAlgorithmImp hashAlg;

    hashAlg.Hash128(d_data, d_length, &d_checksum1, &d_checksum2);
}

const char *CheckedData::GetData() {
    return d_data;
}

//..
// Next, we define 'IsDataValid'. We will generate a checksum from the
// contained data and then compare it to the checksum we generated when the
// class was created. If the two hashes match, then we can be reasonable
// certian that the data is still in a valid state (the chance of an accidental
// collision is very low). If the checksums do not match, we know that the data
// has been corrupted. We will not be able to restore it, but we will know not
// to trust it.
//..

bool CheckedData::IsDataValid() {
    SpookyHashAlgorithmImp hashAlg;
    uint64 checksum1 = 0;
    uint64 checksum2 = 0;

    hashAlg.Hash128(d_data, d_length, &checksum1, &checksum2);

    return (d_checksum1 == checksum1) && (d_checksum2 == checksum2);
}


// ============================================================================
//                            MAIN PROGRAM
// ----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    printf("argc: %i, atoi: %i\n", argc, atoi(argv[1]));
    int                 test = argc > 1 ? atoi(argv[1]) : 0;
    bool             verbose = argc > 2;
    bool         veryVerbose = argc > 3;
    bool     veryVeryVerbose = argc > 4;
    bool veryVeryVeryVerbose = argc > 5;

    printf("TEST " __FILE__ " CASE %d\n", test);

    switch (test) { case 0:
      case 7: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLE
        //   The hashing algorithm can be applied towards useful purposes such
        //   as generating checksums.
        //
        // Concerns:
        //: 1 The usage example provided in the component header file compiles,
        //:   links, and runs as shown.
        //
        // Plan:
        //: 1 Run the usage example (C-1)
        //
        // Testing:
        //   USAGE EXAMPLE
        // --------------------------------------------------------------------
        if (verbose) printf("USAGE EXAMPLE\n"
                            "=============\n");
//..
// Then, we store some data in our 'CheckedData' class for safekeeping.
//..

        char data[] = "To be, or not to be--that is the question:"
                      "Whether 'tis nobler in the mind to suffer"
                      "The slings and arrows of outrageous fortune"
                      "Or to take arms against a sea of troubles"
                      "And by opposing end them. To die, to sleep--"
                      "No more--and by a sleep to say we end"
                      "The heartache, and the thousand natural shocks"
                      "That flesh is heir to. 'Tis a consummation"
                      "Devoutly to be wished. To die, to sleep--"
                      "To sleep--perchance to dream: ay, there's the rub,"
                      "For in that sleep of death what dreams may come"
                      "When we have shuffled off this mortal coil,"
                      "Must give us pause. There's the respect"
                      "That makes calamity of so long life."
                      "For who would bear the whips and scorns of time,"
                      "Th' oppressor's wrong, the proud man's contumely"
                      "The pangs of despised love, the law's delay,"
                      "The insolence of office, and the spurns"
                      "That patient merit of th' unworthy takes,"
                      "When he himself might his quietus make"
                      "With a bare bodkin? Who would fardels bear,"
                      "To grunt and sweat under a weary life,"
                      "But that the dread of something after death,"
                      "The undiscovered country, from whose bourn"
                      "No traveller returns, puzzles the will,"
                      "And makes us rather bear those ills we have"
                      "Than fly to others that we know not of?"
                      "Thus conscience does make cowards of us all,"
                      "And thus the native hue of resolution"
                      "Is sicklied o'er with the pale cast of thought,"
                      "And enterprise of great pitch and moment"
                      "With this regard their currents turn awry"
                      "And lose the name of action. -- Soft you now,"
                      "The fair Ophelia! -- Nymph, in thy orisons"
                      "Be all my sins remembered.";
        CheckedData checkedData(data, strlen(data));

//..
// Now, we check that the 'CheckedData' recognizes that it is still valid.
//..

        ASSERT(checkedData.IsDataValid());

//..
// Finally, we tamper with the data and check that our 'CheckedData' class can
// detect this.
//..
        data[34] = 'z';
        ASSERT(!checkedData.IsDataValid());

      } break;
      case 6: {
        // --------------------------------------------------------------------
        // TESTING HASH64 AND HASH32
        //   Verify that the class offers the ability to invoke 'Hash64' and
        //   'Hash32' with some bytes and a length. Verify that the values
        //   returned matches the hash specified by the canonical SpookyHash
        //   implementation.
        //
        // Concerns:
        //: 1 The functions exists and take a pointer and a length.
        //:
        //: 2 Hashes returned match the data produced by the canonical
        //:   implementation of SpookyHash.
        //
        // Plan:
        //: 1 Check the values returned against the expected results from a
        //:   known good version of the algorithm. (C-1,2)
        //
        // Testing:
        //   static uint64 Hash64(*message, length, seed);
        //   static uint32 Hash32(*message, length, seed);
        // --------------------------------------------------------------------

        if (verbose) printf("\nTESTING HASH64 AND HASH32"
                            "\n=========================\n");

        static const struct {
            int        d_line;
            const char d_value [21];
            uint64     d_hash;
        } SMALLDATA[] = {
#ifdef BSLS_PLATFORM_IS_LITTLE_ENDIAN
       //LINE           VALUE                  HASH
         { L_,                    "1", 0x6c59c5ba0f1773fbLL,},
         { L_,                   "12", 0xd8e4618d7714e777LL,},
         { L_,                  "123", 0x05bf2c12cb95f510LL,},
         { L_,                 "1234", 0x8b674e6d5a0ac743LL,},
         { L_,                "12345", 0xd484bc82cad3e69aLL,},
         { L_,               "123456", 0x94b89813238c7cb6LL,},
         { L_,              "1234567", 0x23697c16fdf58beaLL,},
         { L_,             "12345678", 0xa417b6b27de7737fLL,},
         { L_,            "123456789", 0x05061321ab5a25c5LL,},
         { L_,           "1234567890", 0xca4f2f5e0cf6e52bLL,},
         { L_,          "12345678901", 0x01bd8be90282c58fLL,},
         { L_,         "123456789012", 0x68e036c29482b92dLL,},
         { L_,        "1234567890123", 0xe9b009b4b7decfdbLL,},
         { L_,       "12345678901234", 0x80c7bb4dfc682d3eLL,},
         { L_,      "123456789012345", 0x8baacc9114f4be61LL,},
         { L_,     "1234567890123456", 0x6d991592bc5cdf78LL,},
         { L_,    "12345678901234567", 0x2f64988185dae0f6LL,},
         { L_,   "123456789012345678", 0x7e19bf4284f64decLL,},
         { L_,  "1234567890123456789", 0x8b371c674099f6d2LL,},
         { L_, "12345678901234567890", 0x0d9b5acbdb0ef6a5LL,},
#else
          {L_,                    "1", 0x6c59c5ba0f1773fbLL,},
          {L_,                   "12", 0xd8e4618d7714e777LL,},
          {L_,                  "123", 0x05bf2c12cb95f510LL,},
          {L_,                 "1234", 0xf801826e2579d4e0LL,},
          {L_,                "12345", 0x0c501c63194193b2LL,},
          {L_,               "123456", 0xbe99156e83dd1d84LL,},
          {L_,              "1234567", 0x136b56f84fc2ead5LL,},
          {L_,             "12345678", 0x0a18d2ab074863e1LL,},
          {L_,            "123456789", 0x1bedfd4d45b95a6dLL,},
          {L_,           "1234567890", 0x92c3bf97c1cae0e0LL,},
          {L_,          "12345678901", 0xc3b4bbac31be7a66LL,},
          {L_,         "123456789012", 0xd9705ad4d11507a9LL,},
          {L_,        "1234567890123", 0x0b410618f3d95e93LL,},
          {L_,       "12345678901234", 0x73a3c801de0eaabaLL,},
          {L_,      "123456789012345", 0xd2b700388b94107bLL,},
          {L_,     "1234567890123456", 0xe0c5d5306dc2d204LL,},
          {L_,    "12345678901234567", 0x8be79e229794ed65LL,},
          {L_,   "123456789012345678", 0x99560c0388ae969aLL,},
          {L_,  "1234567890123456789", 0xc3985eb8fcd4afe4LL,},
          {L_, "12345678901234567890", 0x01f9f6f7dd1aeab8LL,},
#endif
        };

        if (verbose) printf("Check the values returned against the expected"
                            " results from a known good version of the"
                            " algorithm. (C-1,2)\n");
        {
            for (int i = 0; i != NUM_DATA; ++i) {
                const int                LINE   = SMALLDATA[i].d_line;
                const char              *VALUE  = SMALLDATA[i].d_value;
                const unsigned long long HASH   = SMALLDATA[i].d_hash;

                if (veryVerbose) printf("Hashing: %s, Expecting: %llu\n",
                                        VALUE,
                                        HASH);

                Obj hash;

                unsigned int hash32 = hash.Hash32(VALUE, strlen(VALUE), 1);
                LOOP_ASSERT(LINE, hash32 == (unsigned int)HASH);

                uint64 hash64 = hash.Hash64(VALUE, strlen(VALUE), 1);
                LOOP_ASSERT(LINE, hash64 == HASH);
            }
        }

      } break;
      case 5: {
        // --------------------------------------------------------------------
        // TESTING HASH128
        //   Verify that the class offers the ability to invoke 'Hash128' with
        //   some bytes and a length. Verify that the values returned matches
        //   the hash specified by the canonical SpookyHash implementation.
        //
        // Concerns:
        //: 1 The function exists and takes a pointer and a length.
        //:
        //: 2 Hashes returned via 'h1' and 'h2' match the data produced by the
        //:   canonical implementation of SpookyHash.
        //
        // Plan:
        //: 1 Check the values returned in 'h1' and 'h2' against the expected
        //:   results from a known good version of the algorithm. (C-1,2)
        //
        // Testing:
        //   static void Hash128(*msg, len, *h1, *h2);
        // --------------------------------------------------------------------

        if (verbose) printf("\nTESTING HASH128"
                            "\n===============\n");

        if (verbose) printf("Check the values returned in 'h1' and 'h2'"
                            " against the expected results from a known good"
                            " version of the algorithm. (C-1,2)\n");
        {
            for (int i = 0; i != NUM_DATA; ++i) {
                const int                LINE   = DATA[i].d_line;
                const char              *VALUE  = DATA[i].d_value;
                const unsigned long long HASH1  = DATA[i].d_hash1;
                const unsigned long long HASH2  = DATA[i].d_hash2;

                if (veryVerbose) printf("Hashing: %s, Expecting: %llu, %llu\n",
                                        VALUE,
                                        HASH1,
                                        HASH2);

                Obj hash;

                uint64 h1 = 1ULL;
                uint64 h2 = 2ULL;
                hash.Hash128(VALUE, strlen(VALUE), &h1, &h2);

                LOOP_ASSERT(LINE, h1 == HASH1);
                LOOP_ASSERT(LINE, h2 == HASH2);
            }
        }

      } break;
      case 4: {
        // --------------------------------------------------------------------
        // TESTING UPDATE
        //   Verify that the class offers the ability to invoke 'Update' with
        //   some bytes and a length. Verify that calling 'Update' will permute
        //   the algorithm's internal state as specified by SpookyHash
        //   (verified by checking 'Final'). Verify that calling 'Update' with
        //   messages incrementally or all at once will return the hash
        //   specified by the canonical SpookyHash implementation.
        //
        // Concerns:
        //: 1 The function exists and takes a pointer and a length.
        //:
        //: 2 Given the same bytes, the function will permute the
        //:   internal state of the algorithm in the same way, regardless of
        //:   whether the bytes are passed in all at once or in pieces.
        //:
        //: 3 'Update' can continue to be used after 'Final' has been called,
        //:   and produces the same values as if 'Final' had never been called.
        //:
        //: 4 Hashes produced by inserting data via 'Update' and calling
        //:  'Final' matches the data produced by the canonical implementation
        //:   of SpookyHash.
        //
        // Plan:
        //: 1 Insert various lengths of c-strings into the algorithm both all
        //:   at once, char by char, and in chunks using 'Update'. Call 'Final'
        //:   periodically between updates. Assert that the algorithm produces
        //:   the same result in all cases. (C-1,2,3)
        //:
        //: 2 Check the output of 'Update' followed by 'Final' against the
        //:   expected results from a known good version of the algorithm.
        //:   (C-4)
        //
        // Testing:
        //   void Update(const void *message, size_t length);
        // --------------------------------------------------------------------

        if (verbose) printf("\nTESTING UPDATE"
                            "\n==============\n");

        if (verbose) printf("Insert various lengths of c-strings into the"
                            " algorithm both all at once, char by char, and in"
                            " chunks using 'Update'. Call 'Final' periodically"
                            " between updates. Assert that the algorithm"
                            " produces the same result in all cases."
                            " (C-1,2,3)\n");
        {
            for (int i = 0; i != NUM_DATA; ++i) {
                const int   LINE  = DATA[i].d_line;
                const char *VALUE = DATA[i].d_value;

                if (veryVerbose) printf("Hashing: %s\n", VALUE);

                Obj contiguousHash;
                Obj charHash;
                Obj chunkHash;

                contiguousHash.Init(1, 2);
                charHash.Init(1, 2);
                chunkHash.Init(1, 2);

                contiguousHash.Update(VALUE, strlen(VALUE));

                for (unsigned int j = 0; j < strlen(VALUE); ++j){
                    if (veryVeryVerbose) printf("Hashing by char: %c\n",
                                                                     VALUE[j]);
                    charHash.Update(&VALUE[j], sizeof(char));

                    uint64 h1;
                    uint64 h2;
                    charHash.Final(&h1, &h2);
                }

                for (unsigned int j = 0; j < strlen(VALUE); j+=2){
                    if (strlen(VALUE) - j == 1) {
                        if (veryVeryVerbose) printf("Hashing by chunk: %c\n",
                                                                     VALUE[j]);
                        chunkHash.Update(&VALUE[j], sizeof(char));
                    } else {

                        if (veryVeryVerbose) printf("Hashing by chunk: %c%c\n",
                                                                   VALUE[j],
                                                                   VALUE[j+1]);
                        chunkHash.Update(&VALUE[j], sizeof(char)*2);
                    }
                }

                uint64 charH1, charH2, chunkH1, chunkH2, contigH1, contigH2;

                charHash.Final(&charH1, &charH2);
                chunkHash.Final(&chunkH1, &chunkH2);
                contiguousHash.Final(&contigH1, &contigH2);

                LOOP_ASSERT(LINE, charH1 == chunkH1 && chunkH1 == contigH1);
                LOOP_ASSERT(LINE, charH2 == chunkH2 && chunkH2 == contigH2);
            }
        }

        if (verbose) printf("Check the output of 'Update' followed by 'Final'"
                            " against the expected results from a known good"
                            " version of the algorithm. (C-4)\n");
        {
            for (int i = 0; i != NUM_DATA; ++i) {
                const int                LINE   = DATA[i].d_line;
                const char              *VALUE  = DATA[i].d_value;
                const unsigned long long HASH1  = DATA[i].d_hash1;
                const unsigned long long HASH2  = DATA[i].d_hash2;

                if (veryVerbose) printf("Hashing: %s, Expecting: %llu, %llu\n",
                                        VALUE,
                                        HASH1,
                                        HASH2);

                Obj hash;
                hash.Init(1, 2);

                hash.Update(VALUE, strlen(VALUE));

                uint64 h1;
                uint64 h2;
                hash.Final(&h1, &h2);

                LOOP_ASSERT(LINE, h1 == HASH1);
                LOOP_ASSERT(LINE, h2 == HASH2);
            }
        }

      } break;
      case 3: {
        // --------------------------------------------------------------------
        // TESTING INITIALIZATION AND FINALIZATION
        //   Verify that the class offers the ability to initialize and
        //   finalize via 'Init' and 'Final' respectively. Verify that calling
        //   'operator()' will permute the algorithm's internal state as these
        //   operators together produces a result that matches the canonical
        //   implementation.  Note that these operators must be tested together
        //   because 'Final' is the only way to access the internal state, and
        //   'Init' must be called for behavior to be defined.
        //
        // Concerns:
        //: 1 Both functions exist.
        //:
        //: 2 Changing the seed used in initialization will change the output
        //:   of the finalization.
        //:
        //: 3 Initializing and finalizing with known values will yeild results
        //:   that match the canonical implementation.
        //:
        //: 4 'Final' can be called multiple times and does not modify the
        //:   state of the algorithm or return different results.
        //
        // Plan:
        //: 1 Initialize the algorithm with various seeds test that permuting
        //:   the seed permutes the output. (C-1,2)
        //:
        //: 2 Use a table of value to check that known seeds will produce
        //:   output that matches the canonical implementation. (C-3)
        //:
        //: 3 Call 'Final' multiple times in a row and test that the result
        //:   that is returned is always the same. (C-4)
        //
        // Testing:
        //   void Init(uint64 seed1, uint64 seed2);
        //   void Final(uint64 *hash1, uint64 *hash2);
        // --------------------------------------------------------------------

        if (verbose) printf("\nTESTING INITIALIZATION AND FINALIZATION"
                            "\n=======================================\n");

        static const struct {
            int    d_line;
            uint64 d_seed1;
            uint64 d_seed2;
            uint64 d_hash1;
            uint64 d_hash2;
        } DATA[] = {
       //LINE  SEED1        SEED2          HASH1                HASH2
     {L_,0x1ea510b7, 0x616d1a49, 0xd5ba52d10c82bac7LL, 0x1c4cfb86447fd4d7LL, },
     {L_,0x1656bae7, 0x68e2e2ff, 0xb899c5b97fce265aLL, 0xf0a107f782a50387LL, },
     {L_,0x041b063c, 0x523c0b0b, 0x251e1e53d514a5e0LL, 0xa56701db799193bfLL, },
     {L_,0x2a0c0f95, 0x711f13b1, 0xe783588309036565LL, 0x011ebe5b2c0234b3LL, },
     {L_,0x2288f3c4, 0x4c8d1ea0, 0x4d29dcd5b5166a20LL, 0xaeffb446aaeccf94LL, },
     {L_,0x27f331e0, 0x39a90b6b, 0xd52120fb51e9097aLL, 0xb50a9e06bec2cbaeLL, },
     {L_,0x674fe63b, 0x2f685346, 0x873f2a409db2943aLL, 0x2e817a5f2b0ace75LL, },
     {L_,0x522edc8b, 0x7a8e2d06, 0x5ff29023ce5000dcLL, 0x29777612702b233dLL, },
     {L_,0x15409676, 0x5c58e2df, 0xa6487995d6549300LL, 0x86abc447512a1fb1LL, },
     {L_,0x4bd025f2, 0x766b6e72, 0xffc72ae31c2b8466LL, 0x69aa1d3dd209a0dfLL, },
     {L_,0x4e150ca9, 0x58510977, 0xc6234210eedd789eLL, 0x7e5e41a3f0a0e47aLL, },
     {L_,0x3706b831, 0x13540a09, 0x3209e96eb6205572LL, 0xf5493459096db176LL, },
     {L_,0x754cb5e5, 0x12c17a8f, 0xa2daaaf5a0f32c31LL, 0x00b5fee8c39fe7f4LL, },
     {L_,0x152437c5, 0x51e69d62, 0x336b49a348305c3aLL, 0x1614bbe7995f7659LL, },
     {L_,0x68dff5a0, 0x7f9e9eee, 0x6dfdb34de52c5856LL, 0x2e1649d249a21f9eLL, },
     {L_,0x171fdb15, 0x07850657, 0x62e20c5d4cfa4e71LL, 0x6e68da4556daa4e9LL, },
     {L_,0x610bb937, 0x2d7695fc, 0x1eaeac87d1aad224LL, 0x8225a6cee81e06fdLL, },
     {L_,0x7067e957, 0x6526bf73, 0x811e14af46de5575LL, 0x2aee9e7113b8a20fLL, },
     {L_,0x7fb2a108, 0x1a73f8ec, 0x2a5ee77b71838a72LL, 0x30e15a2e12fffe30LL, },
     {L_,0x5645d325, 0x223b94cc, 0xbc2543d1a4afc192LL, 0x343895f8eeb8cf01LL, },
     {L_,0x6701178d, 0x7e390505, 0xe67281e302349273LL, 0x9ecc924e1d487eefLL, },
        };
        const int NUM_DATA = sizeof DATA / sizeof *DATA;

        if (verbose) printf("Initialize the algorithm with various seeds test"
                            " that permuting the seed permutes the output."
                            " (C-2)\n");
        {
            uint64 previousH1 = 0;
            uint64 previousH2 = 0;
            uint64 h1;
            uint64 h2;

            for (int i = 0; i != 10; ++i) {
                if (veryVerbose) printf("Testing with seeds: %i, %i\n", i, 0);

                Obj hash;

                hash.Init(i, 0);
                hash.Final(&h1, &h2);

                ASSERT(h1 != previousH1);
                ASSERT(h2 != previousH2);

                previousH1 = h1;
                previousH2 = h2;
            }

            for (int i = 0; i != 10; ++i) {
                if (veryVerbose) printf("Testing with seeds: %i, %i\n", 0, i);

                Obj hash;

                hash.Init(0, i);
                hash.Final(&h1, &h2);

                ASSERT(h1 != previousH1);
                ASSERT(h2 != previousH2);

                previousH1 = h1;
                previousH2 = h2;
            }

            for (int i = 0; i != 10; ++i) {
                if (veryVerbose) printf("Testing with seeds: %i, %i\n", i, i);

                Obj hash;

                hash.Init(i, i);
                hash.Final(&h1, &h2);

                ASSERT(h1 != previousH1);
                ASSERT(h2 != previousH2);

                previousH1 = h1;
                previousH2 = h2;
            }
        }

        if (verbose) printf("Use a table of value to check that known seeds"
                            " will produce output that matches the canonical"
                            " implementation. (C-3)\n");
        {
            for (int i = 0; i != NUM_DATA; ++i) {
                const int    LINE  = DATA[i].d_line;
                const uint64 SEED1 = DATA[i].d_seed1;
                const uint64 SEED2 = DATA[i].d_seed2;
                const uint64 HASH1 = DATA[i].d_hash1;
                const uint64 HASH2 = DATA[i].d_hash2;

                if (veryVerbose) printf("Seeds: %llu, %llu, Expecting: %llu,"
                                        " %llu\n",
                                        SEED1,
                                        SEED2,
                                        HASH1,
                                        HASH2);

                Obj hash;
                hash.Init(SEED1, SEED2);

                uint64 h1;
                uint64 h2;
                hash.Final(&h1, &h2);
                LOOP_ASSERT(LINE, HASH1 == h1);
                LOOP_ASSERT(LINE, HASH2 == h2);
            }
        }

        if (verbose) printf("Call 'Final' multiple times in a row and test"
                            " that the result that is returned is always the"
                            " same. (C-4)\n");
        {
            uint64 previousH1 = 0;
            uint64 previousH2 = 0;
            uint64 h1;
            uint64 h2;
            Obj hash;

            hash.Init(8467435, 2435748);
            hash.Final(&previousH1, &previousH2);

            for (int i = 0; i != 10; ++i) {
                if (veryVerbose) printf("Iteration %i, asserting hashes are"
                                        " equal.\n", i);

                hash.Final(&h1, &h2);

                ASSERT(h1 == previousH1);
                ASSERT(h2 == previousH2);

                previousH1 = h1;
                previousH2 = h2;
            }
        }

      } break;
      case 2: {
        // --------------------------------------------------------------------
        // TESTING IMPLICITLY DEFINED OPERATIONS
        //   Ensure that the four implicitly declared and defined special
        //   member functions are publicly callable.  As there is no observable
        //   state to inspect, there is little to verify other than that the
        //   expected expressions all compile, and
        //
        // Concerns:
        //: 1 Objects can be created using the default constructor.
        //:
        //: 2 Objects can be created using the copy constructor.
        //:
        //: 3 The copy constructor is not declared as explicit.
        //:
        //: 4 Objects can be assigned to from constant objects.
        //:
        //: 5 Assignments operations can be chained.
        //:
        //: 6 Objects can be destroyed.
        //
        // Plan:
        //: 1 Create a default constructed 'SpookyHashAlgorithmImp'. (C-1)
        //:
        //: 2 Use the copy-initialization syntax to create a new instance of
        //:   'SpookyHashAlgorithmImp' from an existing instance. (C-2,3)
        //:
        //: 3 Assign the value of the one (const) instance of
        //:   'SpookyHashAlgorithmImp' to a second. (C-4)
        //:
        //: 4 Chain the assignment of the value of the one instance of
        //:   'SpookyHashAlgorithmImp' to a second instance of
        //:   'SpookyHashAlgorithmImp', into a self-assignment of the second
        //:   object. (C-5)
        //:
        //: 5 Create an instance of 'SpookyHashAlgorithmImp' and allow it to
        //:   leave scope to be destroyed. (C-6)
        //
        // Testing:
        //   SpookyHashAlgorithmImp()
        //   SpookyHashAlgorithmImp(const SpookyHashAlgorithmImp)
        //   ~SpookyHashAlgorithmImp()
        //   SpookyHashAlgorithmImp& operator=(const SpookyHashAlgorithmImp&)
        // --------------------------------------------------------------------

        if (verbose)
            printf("\nTESTING IMPLICITLY DEFINED OPERATIONS"
                   "\n=====================================\n");

        if (verbose) printf("Create a default constructed"
                            " 'SpookyHashAlgorithmImp'. (C-1)\n");
        {
            Obj alg1;
        }

        if (verbose) printf("Use the copy-initialization syntax to create a"
                            " new instance of 'SpookyHashAlgorithmImp' from an"
                            " existing instance. (C-2,3)\n");
        {
            Obj alg1 = Obj();
            Obj alg2 = alg1;
        }

        if (verbose) printf("Assign the value of the one (const) instance of"
                            " 'SpookyHashAlgorithmImp' to a second. (C-4)\n");
        {
            const Obj alg1 = Obj();
            Obj alg2 = alg1;
        }

        if (verbose) printf("Chain the assignment of the value of the one"
                            " instance of 'SpookyHashAlgorithmImp' to a second"
                            " instance of 'SpookyHashAlgorithmImp', into a"
                            " self-assignment of the second object. (C-5)\n");
        {
            Obj alg1 = Obj();
            Obj alg2 = alg1;
            alg2 = alg2 = alg1;
        }

        if (verbose) printf("Create an instance of 'SpookyHashAlgorithmImp'"
                            " and allow it to leave scope to be destroyed."
                            " (C-6)\n");
        {
            Obj alg1;
        }

      } break;
      case 1: {
        // --------------------------------------------------------------------
        // BREATHING TEST
        //   This case exercises (but does not fully test) basic functionality.
        //
        // Concerns:
        //: 1 The class is sufficiently functional to enable comprehensive
        //:   testing in subsequent test cases.
        //
        // Plan:
        //: 1 Create an instance of 'SpookyHashAlgorithmImp'. (C-1)
        //:
        //: 2 Verify different hashes are produced for different c-strings.
        //:   (C-1)
        //:
        //: 3 Verify the same hashes are produced for the same c-strings. (C-1)
        //
        // Testing:
        //   BREATHING TEST
        // --------------------------------------------------------------------

        if (verbose) printf("\nBREATHING TEST"
                            "\n==============\n");

        if (verbose) printf("Instantiate 'SpookyHashAlgorithmImp'\n");
        {
            Obj spookyImp;
        }

        if (verbose) printf("Verify different hashes are produced for"
                            " different c-strings. (C-1)\n");
        {
            Obj spookyImp;
            const char *str1 = "123456";
            const char *str2 = "654321";
            ASSERT(spookyImp.Hash32(str1, sizeof(char)*6, 0) !=
                   spookyImp.Hash32(str2, sizeof(char)*6, 0));

            ASSERT(spookyImp.Hash64(str1, sizeof(char)*6, 0) !=
                   spookyImp.Hash64(str2, sizeof(char)*6, 0));

            uint64 hash1a = 0ULL;
            uint64 hash1b = 0ULL;
            spookyImp.Hash128(str1, sizeof(char)*6, &hash1a, &hash1b);
            uint64 hash2a = 0ULL;
            uint64 hash2b = 0ULL;
            spookyImp.Hash128(str2, sizeof(char)*6, &hash2a, &hash2b);

            ASSERT(hash1a != 0ULL && hash1b != 0ULL);
            ASSERT(hash1a != hash2a);
            ASSERT(hash1b != hash2b);
        }

        if (verbose) printf("Verify the same hashes are produced for the same"
                            " c-strings. (C-1)\n");
        {
            Obj spookyImp;
            const char *str1 = "123456";
            const char *str2 = "123456";
            ASSERT(spookyImp.Hash32(str1, sizeof(char)*6, 0) ==
                   spookyImp.Hash32(str2, sizeof(char)*6, 0));

            ASSERT(spookyImp.Hash64(str1, sizeof(char)*6, 0) ==
                   spookyImp.Hash64(str2, sizeof(char)*6, 0));

            uint64 hash1a = 0ULL;
            uint64 hash1b = 0ULL;
            spookyImp.Hash128(str1, sizeof(char)*6, &hash1a, &hash1b);
            uint64 hash2a = 0ULL;
            uint64 hash2b = 0ULL;
            spookyImp.Hash128(str2, sizeof(char)*6, &hash2a, &hash2b);

            ASSERT(hash1a != 0ULL && hash1b != 0ULL);
            ASSERT(hash1a == hash2a);
            ASSERT(hash1b == hash2b);
        }
      } break;
      default: {
        fprintf(stderr, "WARNING: CASE `%d' NOT FOUND.\n", test);
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        fprintf(stderr, "Error, non-zero test status = %d.\n", testStatus);
    }

    return testStatus;
}

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Bloomberg Finance L.P.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------- END-OF-FILE ----------------------------------

