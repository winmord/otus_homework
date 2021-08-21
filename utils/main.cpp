#include <fstream>
#include <filesystem>
#include <string>

std::string get_interface_name(std::filesystem::path const& file_path)
{
	auto generated_file_name = file_path.filename().string();
	return std::string(generated_file_name.begin(),
	                   generated_file_name.begin() + generated_file_name.rfind("."));
}

std::string get_generated_class_name(std::filesystem::path const& file_path)
{
	auto generated_file_name = file_path.filename().string();
	return std::string(generated_file_name.begin() + 2,
	                   generated_file_name.begin() + generated_file_name.rfind(".")) +
		"_adapter";
}

std::vector<std::string> get_interface_functions(std::filesystem::path const& interface_path)
{
	std::vector<std::string> interface_functions;
	std::ifstream interface_stream(interface_path);
	std::string interface_name = interface_path.filename().string();
	interface_name = std::string(interface_name.begin(), interface_name.begin() + interface_name.find("."));

	std::string current_file_string;

	while (std::getline(interface_stream, current_file_string))
	{
		if (current_file_string.find(" = 0;") == std::string::npos) continue;

		std::string function_definition = std::string(current_file_string.begin() + current_file_string.find(" ") + 1,
		                                              current_file_string.begin() + current_file_string.find(" = 0;"));
		function_definition += std::string(" override\n\t\t{\n\t\t\t");

		if (function_definition.find(" get_") != std::string::npos)
		{
			function_definition += "return *ioc_provider::IoC.resolve<" +
				std::string(function_definition.begin(),
				            function_definition.begin() + function_definition.find(" ")) + ">(\"" +
				"tank.operations." + interface_name + ":" + 
				std::string(function_definition.begin() + function_definition.find(" ") + 1,
				            function_definition.begin() + function_definition.find("(")) + "\", obj_);";
		}

		if (function_definition.find(" set_") != std::string::npos)
		{
			const auto arguments = std::string(function_definition.begin() + function_definition.find("(") + 1,
			                                   function_definition.begin() + function_definition.find(")"));

			function_definition += "ioc_provider::IoC.resolve(\"tank.operations." + interface_name + ":" +
				std::string(function_definition.begin() + function_definition.find(" ") + 1,
				            function_definition.begin() + function_definition.find("(")) + "\", obj_, " +
				std::string(arguments.begin() + arguments.rfind(" ") + 1, arguments.end()) + ");";
		}

		function_definition += "\n\t\t}\n\n";

		interface_functions.push_back(function_definition);
	}

	interface_stream.close();

	return interface_functions;
}

int main(int argc, char** argv)
{
	const std::filesystem::path source_directory_folder_path = argv[1];
	const std::filesystem::path source_file_name = argv[2];
	std::filesystem::path generated_header_file_path = argv[3];

	const auto string_source_file_name = source_file_name.string();

	if (string_source_file_name.find("interface") != std::string::npos)
	{
		if (string_source_file_name.find("i_command.hpp") != std::string::npos ||
			string_source_file_name.find("i_uobject.hpp") != std::string::npos)
			return 0;

		const auto interface_name = get_interface_name(source_file_name);
		const auto generated_class_name = get_generated_class_name(source_file_name);

		generated_header_file_path = source_directory_folder_path / generated_header_file_path / std::string(generated_class_name + ".hpp");

		const auto interface_functions = get_interface_functions(source_directory_folder_path / source_file_name);

		std::ofstream generated_header_stream(generated_header_file_path);
		generated_header_stream << "#pragma once\n"
			<< "#include <memory>\n\n"
			<< "#include \"otus_homework/globals.hpp\"\n"
			<< "#include \"otus_homework/interfaces/i_uobject.hpp\"\n"
			<< "#include \"" +
			std::string(string_source_file_name.begin() + string_source_file_name.find("/") + 1,
			            string_source_file_name.end()) + "\"\n\n"
			<< "namespace tank_battle_server\n{\n"
			<< "\tclass " + generated_class_name + " : public " + interface_name + "\n\t{\n\tpublic:\n"
			<< "\t\texplicit " + generated_class_name + "(std::shared_ptr<i_uobject> obj)\n\t\t\t: obj_(std::move(obj))\n\t\t{}\n\n";

		for (auto const& fun : interface_functions)
		{
			generated_header_stream << "\t\t" + fun;
		}

		generated_header_stream << "\tprivate:\n\t\tstd::shared_ptr<i_uobject> obj_;\n\t};\n}";


		generated_header_stream.close();
	}

	return 0;
}
