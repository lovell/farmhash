// Copyright 2014 Lovell Fuller and others.
// SPDX-License-Identifier: Apache-2.0

const { familySync, MUSL } = require('detect-libc');

const libc = familySync() === MUSL ? 'musl' : '';

module.exports = `${process.platform}${libc}-${process.arch}`;
