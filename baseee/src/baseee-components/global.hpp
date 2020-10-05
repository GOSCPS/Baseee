/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * THIS FILE IS FROM Chhdao(sudo.free@qq.com)
 * IS LICENSED UNDER MIT
 * File:     global.hpp
 * Content:  components  module file for global
 * Copyright (c) 2020 Chhdao All rights reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once


namespace baseee {
	namespace components {

		template<typename T>
		static class Global {
		public:

			void Set(T t) noexcept {
				this->t = t;
			}

			T Get() noexcept {
				return T;
			}

		private:
			T t;
		};

	}
}