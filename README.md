# farmhash

Node.js implementation of Google's
[FarmHash](https://github.com/google/farmhash)
family of very fast hash functions.

FarmHash is the successor to CityHash.
Functions in the FarmHash family are not suitable for cryptography.
A fast, cryptographically-secure alternative is
[HighwayHash](https://github.com/lovell/highwayhash).

The 32-bit methods return a `Number`,
the 64-bit methods return a `BigInt`
and the 128-bit methods are not implemented.

This module uses FarmHash v1.1.0 (2015-03-01).
It has been tested with Node.js 16, 18, 20 and 22
on Linux (glibc, musl),
macOS (x64, arm64) and
Windows (x86, x64).

Pre-compiled binaries are provided for
Intel CPUs with SSE4.2 intrinsics
and Apple ARM64 CPUs.
Use the `npm install --build-from-source` flag to gain performance benefits
on more modern CPUs such as those with AVX intrinsics.

## Installation

```sh
npm install farmhash
```

```sh
yarn add farmhash
```

```sh
pnpm add farmhash
```

## Usage

```javascript
const farmhash = require('farmhash');
```

```javascript
const hash = farmhash.hash32('test');
console.log(typeof hash); // 'number'
```

```javascript
const hash = farmhash.hash64(new Buffer('test'));
console.log(typeof hash); // 'bigint'
```

```javascript
const hash = farmhash.hash64WithSeed('test', 123);
console.log(typeof hash); // 'bigint'
```

```javascript
const hash = farmhash.fingerprint32(new Buffer('test'));
console.log(typeof hash); // 'number'
```

```javascript
const hash = farmhash.fingerprint64('test');
console.log(typeof hash); // 'bigint'
```

```javascript
const hash = farmhash.fingerprint64signed('test');
console.log(typeof hash); // 'bigint'
```

## API

### Hash

The hash methods are platform dependent.
Different CPU architectures, for example 32-bit vs 64-bit, Intel vs ARM, SSE4.2 vs AVX
might produce different results for a given input.

#### hash32(input)

* `input` is the `Buffer` or `String` to hash.

Returns a `Number` containing the 32-bit unsigned integer hash value of `input`.

#### hash32WithSeed(input, seed)

* `input` is the `Buffer` or `String` to hash.
* `seed` is an integer Number to use as a seed.

Returns a `Number` containing the 32-bit unsigned integer hash value of `input`.

#### hash64(input)

* `input` is the `Buffer` or `String` to hash.

Returns a `BigInt` containing the 64-bit unsigned integer hash value of `input`.

#### hash64WithSeed(input, seed)

* `input` is the `Buffer` or `String` to hash.
* `seed` is an integer `Number` to use as a seed.

Returns a `BigInt` containing the 64-bit unsigned integer hash value of `input`.

#### hash64WithSeeds(input, seed1, seed2)

* `input` is the `Buffer` or `String` to hash.
* `seed1` and `seed2` are both an integer `Number` to use as seeds.

Returns a `BigInt` containing the 64-bit unsigned integer hash value of `input`.

### Fingerprint

The fingerprint methods are platform independent, producing the same results for a given input on any machine.

#### fingerprint32(input)

* `input` is the `Buffer` or `String` to fingerprint.

Returns a `Number` containing the 32-bit unsigned integer fingerprint value of `input`.

#### fingerprint64(input)

* `input` is the `Buffer` or `String` to fingerprint.

Returns a `BigInt` containing the 64-bit unsigned integer fingerprint value of `input`.

#### fingerprint64signed(input)

* `input` is the `Buffer` or `String` to fingerprint.

Returns a `BigInt` containing the 64-bit signed integer fingerprint value of `input`.

This matches the signed behaviour of Google BigQuery's
[FARM_FINGERPRINT](https://cloud.google.com/bigquery/docs/reference/standard-sql/functions-and-operators#farm_fingerprint)
function.

## Testing

```sh
npm test
```

## Licence

Copyright 2014 Lovell Fuller and contributors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     https://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Copyright 2014, 2015, 2016, 2017 Google, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
