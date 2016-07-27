# farmhash

Node.js implementation of Google's
[FarmHash](https://github.com/google/farmhash)
family of very fast hash functions.

FarmHash is the successor to CityHash.
Functions in the FarmHash family are not suitable for cryptography.
A fast, cryptographically-secure alternative is
[HighwayHash](https://github.com/lovell/highwayhash).

As the V8 JavaScript engine only natively supports 32-bit unsigned integers,
the 64-bit methods return strings instead of Numbers
and the 128-bit methods are not implemented.

This module uses FarmHash v1.1.0 (2015-03-01).
It has been tested with Node.js v0.10, v0.12, v4, v6
on Linux, OS X and Windows.

## Installation

```sh
npm install farmhash
```

## Usage

```javascript
var farmhash = require('farmhash');
```

```javascript
var hash = farmhash.hash32('test');
console.log(typeof hash); // 'number'
```

```javascript
var hash = farmhash.hash64(new Buffer('test'));
console.log(typeof hash); // 'string'
```

```javascript
var hash = farmhash.hash64WithSeed('test', 123);
console.log(typeof hash); // 'string'
```

```javascript
var hash = farmhash.fingerprint32(new Buffer('test'));
console.log(typeof hash); // 'number'
```

```javascript
var hash = farmhash.fingerprint64('test');
console.log(typeof hash); // 'string'
```

## API

### Hash

The hash methods are platform dependent.
Different CPU architectures, for example 32-bit vs 64-bit, Intel vs ARM, SSE4.2 vs AVX
might produce different results for a given input.

#### hash32(input)

* `input` is the Buffer or String to hash.

Returns a Number containing the 32-bit unsigned integer hash value of `input`.

#### hash32WithSeed(input, seed)

* `input` is the Buffer or String to hash.
* `seed` is an integer Number to use as a seed.

Returns a Number containing the 32-bit unsigned integer hash value of `input`.

#### hash64(input)

* `input` is the Buffer or String to hash.

Returns a String representing the 64-bit unsigned integer hash value of `input`.

#### hash64WithSeed(input, seed)

* `input` is the Buffer or String to hash.
* `seed` is an integer Number to use as a seed.

Returns a String representing the 64-bit unsigned integer hash value of `input`.

#### hash64WithSeeds(input, seed1, seed2)

* `input` is the Buffer or String to hash.
* `seed1` and `seed2` are integer Numbers to use as seeds.

Returns a String representing the 64-bit unsigned integer hash value of `input`.

#### hash32v1(input)

Legacy function to access v1 of the FarmHash implementation.

* `input` is the Buffer or String to hash.

Returns a Number containing the 32-bit unsigned integer v1 hash value of `input`.

### Fingerprint

The fingerprint methods are platform independent, producing the same results for a given input on any machine.

#### fingerprint32(input)

* `input` is the Buffer or String to fingerprint.

Returns a Number containing the 32-bit unsigned integer fingerprint value of `input`.

#### fingerprint64(input)

* `input` is the Buffer or String to fingerprint.

Returns a String representing the 64-bit unsigned integer fingerprint value of `input`.

## Testing

[![Build Status](https://travis-ci.org/lovell/farmhash.png?branch=master)](https://travis-ci.org/lovell/farmhash)

[![Build status](https://ci.appveyor.com/api/projects/status/es9kgsucfhmg8j0l)](https://ci.appveyor.com/project/lovell/farmhash)

```sh
npm test
```

## Licence

Copyright 2014, 2015, 2016 Lovell Fuller and contributors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Copyright 2014, 2015 Google, Inc.

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
