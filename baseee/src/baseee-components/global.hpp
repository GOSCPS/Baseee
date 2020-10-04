/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * THIS FILE IS FROM Chhdao(sudo.free@qq.com)
 * IS LICENSED UNDER MIT
 * File:     global.hpp
 * Content:  components  module file for global
 * Copyright (c) 2020 Chhdao All rights reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



namespace baseee {
	namespace components {

		template<typename T>
		static class Global {
		public:

			void Set(T t) {
				this->t = t;
			}

			T Get() {
				return T;
			}

		private:
			T t;
		};

	}
}






