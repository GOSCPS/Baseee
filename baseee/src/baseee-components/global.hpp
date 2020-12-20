/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ����ļ����� GOSCPS(https://github.com/GOSCPS)
 * ʹ�� GOSCPS ���֤
 * File:    global.hpp
 * Content: global Source File
 * Copyright (c) 2020 GOSCPS ��������Ȩ��.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once

#include <set>
#include <map>

namespace baseee {
	namespace components {

		static class KeyManager {
		public:
			
			//��ȡһ��Key
			static uint64_t GetFreeKey() {
				//����п�ȱ��λ�ã�����
				if (Space.size() != 0) {
					auto it = Space.begin();
					auto buf = *it;
					Pool.insert(*it);
					Space.erase(it);
					return buf;
				}
				//û����ʹ����һ��λ��
				else {
					Pool.insert(NextKey);
					NextKey++;
					return NextKey - 1;
				}
			}

			//Key�Ƿ�����ʹ��
			static bool IsUsed(uint64_t Key) {
				if (Pool.find(Key) != Pool.cend())
					return true;
				else return false;
			}

			//�ͷ�һ��Key
			static void FreeKey(uint64_t Key) {
				if (Pool.find(Key) == Pool.cend())
					return;
				else {
					auto it = Pool.find(Key);
					Space.insert(*it);//��ӵ���ȱλ��
					Pool.erase(it);//������ʹ����ɾ��
					return;
				}
			}

		private:
			static uint64_t NextKey = 0;
			static std::set<uint64_t> Space;//��ȱ��
			static std::set<uint64_t> Pool;//ʹ�ó�
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