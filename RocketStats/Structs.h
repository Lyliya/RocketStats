#pragma once
#include "pch.h"

namespace NS_RS {
	struct Stats {
		float myMMR = 600.0f;
		float MMRChange = 0.0f;
		int win = 0;
		int losses = 0;
		int streak = 0;
		bool isInit = 0;
	};

	typedef struct s_ranks {
		std::string name;
		std::shared_ptr<ImageWrapper> image;
	} t_ranks;
}