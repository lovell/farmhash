export function fingerprint32(input: string | Buffer): number;

export function fingerprint64(input: string | Buffer): BigInt;

export function fingerprint64signed(input: string | Buffer): BigInt;

export function hash32(input: string | Buffer): number;

export function hash32WithSeed(input: string | Buffer, seed: number): number;

export function hash64(input: string | Buffer): BigInt;

export function hash64WithSeed(input: string | Buffer, seed: number): BigInt;

export function hash64WithSeeds(input: string | Buffer, seed1: number, seed2: number): BigInt;
