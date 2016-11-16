/*******************************************************
 * Copyright (C) 2014 iQIYI.COM - All Rights Reserved
 * 
 * This file is part of {HCDN}.
 * Unauthorized copy of this file, via any medium is strictly prohibited.
 * Proprietary and Confidential.
 * 
 * Author(s): zenglinan <zenglinan@qiyi.com>
 * 
 *******************************************************/
/*PSL(PPStream Standard Library)
 */
#pragma once
#if defined(__cplusplus)
	#define	_PSL	psl_live
	#define	_NAMESPACE_BEGIN	namespace psl_live {
	#define	_NAMESPACE_END	}
	#define	_C_DECL_BEGIN	extern "C" {
	#define _C_DECL_END	}
#else
	#define	_PSL
	#define	_PSL_BEGIN
	#define	_PSL_END
	#define	_C_DECL_BEGIN
	#define	_C_DECL_END
#endif
