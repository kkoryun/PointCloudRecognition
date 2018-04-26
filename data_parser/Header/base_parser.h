#pragma once

#include <string>

namespace Parsers {

	class Parser
	{
	public:
		explicit Parser(std::string dataPath = "") {
			m_dataPath = dataPath;
		}

		void setFilePath(std::string dataPath) {
			auto it = dataPath.end() - 1;
			if(*it != '/')
			{
				dataPath.push_back('/');
			}

			m_dataPath = dataPath;
		}
		std::string getFilePath() const {
			return m_dataPath;
		}
	protected:
		virtual void parse() = 0;
		virtual ~Parser(){}

	protected:

		std::string m_dataPath;
	};
}