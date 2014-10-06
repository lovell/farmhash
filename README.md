# farmhash

Node.js implementation of Google's [FarmHash](https://code.google.com/p/farmhash/) family of very fast hash functions.

FarmHash is the successor to CityHash.

Functions in the FarmHash family are not suitable for cryptography.

As V8 does not natively support 64 bit unsigned integers this module returns hash values as String objects.

Compiled and tested with Node.js v0.10 (stable) and v0.11 (unstable).

## Installation

```
npm install farmhash
```

## Usage

```javascript
var farmhash = require('farmhash');
```

```javascript
var hash = farmhash.Hash64(string);
```

## API

### Hash64(string)

Return a String representing the 64 bit unsigned integer hash value of the input `string`.

## Testing

[![Build Status](https://travis-ci.org/lovell/farmhash.png?branch=master)](https://travis-ci.org/lovell/farmhash)

```
npm test
```

## Licence

Copyright 2014 Lovell Fuller

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
[http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0.html)

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Copyright 2014 Google, Inc.

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
