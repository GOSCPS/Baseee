/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 这个文件来自 GOSCPS(https://github.com/GOSCPS)
 * 使用 GOSCPS 许可证
 * File:    global.hpp
 * Content: global Source File
 * Copyright (c) 2020 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once

#include <set>
#include <map>

namespace baseee {
	namespace components {

		static class KeyManager {
		public:
			
			//获取一个Key
			static uint64_t GetFreeKey() {
				//如果有空缺的位置，补上
				if (Space.size() != 0) {
					auto it = Space.begin();
					auto buf = *it;
					Pool.insert(*it);
					Space.erase(it);
					return buf;
				}
				//没有则使用下一个位置
				else {
					Pool.insert(NextKey);
					NextKey++;
					return NextKey - 1;
				}
			}

			//Key是否正在使用
			static bool IsUsed(uint64_t Key) {
				if (Pool.find(Key) != Pool.cend())
					return true;
				else return false;
			}

			//释放一个Key
			static void FreeKey(uint64_t Key) {
				if (Pool.find(Key) == Pool.cend())
					return;
				else {
					auto it = Pool.find(Key);
					Space.insert(*it);//添加到空缺位置
					Pool.erase(it);//从正在使用中删除
					return;
				}
			}

		private:
			static uint64_t NextKey = 0;
			static std::set<uint64_t> Space;//空缺池
			static std::set<uint64_t> Pool;//使用池
		};


		template<typename T>
		class Global {
		public:

			static void Set(int64_t Key,T t) noexcept {
				this->t[Key] = t;
			}

			static T Get(int64_t Key) noexcept {
				return t[Key];
			}

		private:
			std::map<int64_t,T> t;
		};

		template<typename T>
		Global::t = std::map<int64_t, T>();


	}
}