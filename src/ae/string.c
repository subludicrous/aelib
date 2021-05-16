// © Nikola Stepanoski
// SPDX-License-Identifier: BSL-1.0

#include <ae/string.h>
#include <errno.h>
#include <stdlib.h>

void uint_to_binstr_base(char * binstr, uint64_t const val, size_t const bits) {
	for (uint64_t i = 0x1Ui64 << (bits - 1Ui64); i; i >>= 1U) {
		*binstr = (val & i) ? '1' : '0';
		binstr++;
	}
}

int AEAPI uint_to_binstr(char * const binstr, uint64_t const val, size_t const bits) {
	if (!binstr || !bits || bits > 64Ui64) {
		return EINVAL;
	}
	uint_to_binstr_base(binstr, val, bits);
	return 0;
}

char * AEAPI auint_to_binstr(uint64_t const input, size_t const bits) {
	if (bits > 64i64) return NULL;

	char * const output = malloc(bits + 1Ui64);
	if (!output) {
		return NULL;
	}
#if _MSC_VER
#pragma warning(disable: 6386)
#endif
	output[bits] = '\0';
	uint_to_binstr_base(output, input, bits);
	return output;
}
