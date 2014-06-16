#pragma once

#include <string>
#include <map>
#include <memory>

namespace faod
{

	template <typename Resource, typename Ident>
	class ResourceHolder
	{
		public:
			void load(Ident id, const std::string& filename);
			
			template <typename Parameter>
			void load(Ident id, const std::string& filename, const Parameter& param);

			Resource& 		get(Ident id);
			const Resource& get(Ident id) const;


		private:
			std::map<Ident, std::unique_ptr<Resource>> resources_;
	};

};

#include "ResourceHolder.inl"
