export function fingerprint32(input: string | Buffer): number;

export function fingerprint64(input: string | Buffer): bigint;

export function fingerprint64signed(input: string | Buffer): bigint;

export function hash32(input: string | Buffer): number;

export function hash32WithSeed(input: string | Buffer, seed: number): number;

export function hash64(input: string | Buffer): bigint;

export function hash64WithSeed(input: string | Buffer, seed: number): bigint;

export function hash64WithSeeds(input: string | Buffer, seed1: number, seed2: number): bigint;
