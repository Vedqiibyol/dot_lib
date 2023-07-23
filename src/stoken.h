#ifndef DSTL_STRING_EXT
#define DSTL_STRING_EXT

#include "../types"

namespace DSTL {
	u16	StrCountN(
		const	char*	str,		// Base string
		const	char*	sep,		// String of separators
			u16	start,
			u16	end,
		const	char*	wordw		// String of word wrappers
	) {
		if(sep == nullptr || wordw == nullptr) return -1;

		bool	wr	= false;											// Word wrapper flag
		char	wch	= 0;												// word separator character
		char	_ch	= 0;												// Buffer
		u16	occ	= 0;
		u16	count	= 0;

		auto IsSep = [&](u16 p) -> bool {										// Is separator 'lbd
			if(wr) return false;
			for(u16 j=0; sep[j]; j++)
				if(sep[j] == str[p]) return true;
			return false;
		};
		auto IsWordW = [&](u16 p) -> char {										// Is word wrapper 'lbd
			for(u16 j=0; wordw[j]; j++)
				if(wordw[j] == str[p]) return wordw[j];
			return 0;
		};

		for(; str[start] && start <= end; start++) {
			wch = IsWordW(start);

			occ++;

			if(!wr) {
				if(wch && occ == 1) {
					_ch = wch;
					occ = 0;
					wr  = true;
				} else {
					if(IsSep(start)) occ = 0;
				}
			} else {
				if(_ch == wch) {
					wr  = false;
					occ = 0;
				}
			}

			if(occ == 1) count++;
		}

		return count;
	}

	u16	StrFindN(
		const	char*	str,		// base string
		const	char*	target,
		const	char*	sep,		// separators
			u16	occ,		// what occurence
			u16	start,
			u16	end,
		const	char*	wordw		// word wrapper (ex: '', "", ``)
	) {
		bool sch  = false;												// Separator flag
		u16 socc  = 0;
		bool wr   = false;												// Word wrapper flag
		char wch  = 0;													// word separator character
		char _ch  = 0;													// Buffer


		auto IsSep = [&](u16 p) -> bool {										// Is separator 'lbd
			for(u16 i=0; sep[i]; i++)
				if(sep[i] == str[p]) return true;
			return false;
		};
		auto IsWordW = [&](u16 p) -> char {										// Is word wrapper 'lbd
			for(u16 i=0; wordw[i]; i++)
				if(wordw[i] == str[p]) return wordw[i];
			return 0;
		};

		auto IsTarget = [&]() -> bool {
			u16 i=0;
			for(; target[i] && str[start+i+wr] && start+i+wr <= end; i++) {
				if(wr) {											// if between 'ws
					if(_ch == IsWordW(start+i+wr))	break;							// if at the end
				} else {
					if(IsSep(start+i+wr)) break;								// if not, then if there is a separator
				}

				if(str[start+i+wr] != target[i]) break;								// basic Find-check
			}

			if(!target[i])	return true;										// black magic
			else		return false;
		};


		for(; str[start] && start <= end; start++) {
			socc++;

			wch = IsWordW(start);											// 'ww save

			if(!wr) {
				sch = IsSep(start);
				if(sch) socc = 0;

				if(wch) {											// if inside
					if(socc == 1) {
						if(!_ch) {
							_ch = wch;
							wr	= wch;
						} else socc = 0;
					}
				}
			} else {
				if(_ch == wch) {
					wr = false;										// if out of 'ww [...]
					_ch = 0;
					socc = 0;
				}
			}

			if((!sch || wr) && socc == 1) {
				if(IsTarget()) {
					if(occ)		occ--;
					else	return	start + wr;
				}
			}
		}

		return -1;													// default
	}

	u16	StrFindNIndex(
		const	char*	str,
		const	char*	target,
			u16	from,
			u16	occ,
		const	char*	sep,
			u16	start,
			u16	end,
		const	char*	wordw
	) {
		bool wr  = false;												// Word wrapper flag
		char wch = 0;													// word separator character
		char _ch = 0;													// Buffer
		u16 occ2 = 0;													// element occurence

		auto IsSep = [&](u16 p) -> bool {										// Is separator 'lbd
			if(wr) return false;
			for(u16 j=0; sep[j]; j++)
				if(sep[j] == str[p]) return true;
			return false;
		};
		auto IsWordW = [&](u16 p) -> char {										// Is word wrapper 'lbd
			for(u16 j=0; wordw[j]; j++)
				if(wordw[j] == str[p]) return wordw[j];
			return 0;
		};

		auto IsTarget = [&]() -> bool {
			u16 i=0;
			for(; target[i] && str[start+i+wr] && start+i+wr <= end; i++) {
				if(wr) {											// if between 'ws
					if(_ch == IsWordW(start+i+wr))	break;							// if at the end
				} else {
					if(IsSep(start+i+wr)) break;								// if not, then if there is a separator
				}

				if(str[start+i+wr] != target[i]) break;								// basic Find-check
			}

			if(!target[i])	return true;										// black magic
			else		return false;
		};

		u16 index = 0;
		for(; str[start] && start <= end; start++) {
			wch = IsWordW(start);

			occ2++;

			if(!wr) {
				if(wch && occ == 1) {
					_ch  = wch;
					occ2 = 0;
					wr   = true;
				} else {
					if(IsSep(start)) occ = 0;
				}
			} else {
				if(_ch == wch) {
					wr   = false;
					occ2 = 0;
				}
			}

			if(!from){
				if(occ2 == 1) {
					if(IsTarget()) return index;
					index++;
				}
			} else from--;
		}

		return -1;
	}

	u32	StrSplitN(
		const	char*	str,
			char*	output,
			u16*	indices,
			u16	outlen,
			u16	inxlen,
		const	char*	sep,
			u16	start,
			u16	end,
		const	char*	wordw,
			u16	from
	) {
		bool wr  = false;												// Word wrapper flag
		char wch = 0;													// word separator character
		char _ch = 0;													// Buffer
		u16 occ  = 0;													// element occurence

		auto IsSep = [&](u16 p) -> bool {										// Is separator 'lbd
			if(wr) return false;
			for(u16 j=0; sep[j]; j++)
				if(sep[j] == str[p]) return true;
			return false;
		};
		auto IsWordW = [&](u16 p) -> char {										// Is word wrapper 'lbd
			for(u16 j=0; wordw[j]; j++)
				if(wordw[j] == str[p]) return wordw[j];
			return 0;
		};

		u16 cnt = 0;
		u16 pos = 0;
		for(; str[start] && start <= end && pos <= outlen && cnt <= inxlen; start++) {
			wch = IsWordW(start);

			occ++;

			if(!wr) {
				if(wch && occ == 1) {
					_ch = wch;
					occ = 0;
					wr  = true;
				} else {
					if(IsSep(start)) occ = 0;
				}
			} else {
				if(_ch == wch) {
					wr  = false;
					occ = 0;
				}
			}

			if(!from){
				if(occ == 1) {
					if(pos > 1) {
						output[pos] = '\0';
						pos++;
					}
					indices[cnt] = pos;
					cnt++;
				}
				if(occ) {
					output[pos] = str[start];
					pos++;
				}
			} else from--;
		}

		return cnt;
	}


	u16	StrJoinN(
		const	char*	src,
		const	u16*	inx,
			u16	cnt,
			char*	output,
			u16	outlen,
			char	chr
	) {
		u16 i=0, j=0, k=0;
		for(; i<=outlen && j<cnt; i++) {
			if(src[inx[j]+k]) {
				output[i] = src[inx[j]+k];
				k++;
			} else {
				j++;
				k=0;
				if(!chr) continue;

				else output[i] = chr;
			}
		}

		output[i] = '\0';

		return i;
	}


	u16	StrSplit(
		const	char*	str,
			char*	output,
			u16	xlen,
			u16	ylen,
			char	sep
	) {
		u16 k = 0;
		bool f = false;
		for(u16 i=0, x=0, y=0; str[i]; i++) {
			if(str[i] == sep) {
				if(y+1 < ylen) output[ylen*x+y+1] = 0;
				y = 0;
				if(!f) x++;
				f = true;
			} else {
				if(x < xlen && y < ylen) {
					output[ylen*x+y] = str[i];
				}
				y++;
				f = false;
				k++;
			}
		}

		return k;
	}

	u16	StrJoin(
		const	char*	strs,
			char*	output,
			u16	outlen,
			u16	elem,
			u16	elemsize,
			char	joiner
	) {
		u16 k = 0;
		for(u16 i=0; i < elem; i++, k++) {
			for(u16 j=0; strs[elemsize*i+j] && k <= outlen; j++, k++) {
				output[k] = strs[elemsize*i+j];
			}
			output[k] = joiner;
		}
		output[k-1] = 0;

		return k;
	}
}

#endif /* DSTL_STRING_EXT */

#ifndef DSTL_STRING_TRIM
#define DSTL_STRING_TRIM

#include "../types"

#include <iostream>

namespace DSTL {
	u16	StrTrim(
		char*	str,
		s32	pos,
		u16	size,
		bool	stack
	) {
		char* p = str;
		while(*p) p++;
		u16 len = p - str;

		s32 rpos = pos;
		if(pos < 0) rpos = len + pos + 1 - size; // len - abs(pos) + 1 - size
		if(rpos > len) return 0;
		if(size >= len - rpos) size = len - rpos;

		if(rpos + size >= len) stack = 0;

		u16 i = 0;
		for(; i < size; i++) {
			str[rpos+i] = 0;
		}

		if(stack) {
			for(u16 j=0; rpos + size + j <= len; j++)
				str[rpos+j] = str[rpos+size+j];
		}

		return i;
	}

	u16	StrStrip(
			char*	str,
		const	char*	target,
			u16	length,
			u16	start,
			u16	end,
			bool	stack
	) {
		if(end < 0) {
			char* p = (char*)str;
			while(*p) p++;
			end = p - str - end * -1 + 1;
		}

		auto IsTarget = [&](char c) -> char {
			for(u16 _=0; target[_]; _++)
				if(target[_] == c) return c;
			return 0;
		};

		u16 k = 0;
		for(u16 i=start; str[i] && i <= end; i++, k++) {
			if(IsTarget(str[i])) {
				u16 c=0;
				for(u16 j=i; str[j] && j <= end; j++) {
					if(IsTarget(str[j])) { c++; k++; }
					else break;
				}
				if(c) {
					StrTrim(str, i, c, true);
				}
			}
		}

		return k;
	}
}

#endif /* DSTL_STRING_TRIM */


