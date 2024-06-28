#pragma once

#include <filesystem>
#include <string>
#include <vector>

/**
 * @brief テンプレートのデフォルトディレクトリの一覧を返す
 * @param direcotryName ファイルのディレクトリ名
 * @return ディレクトリパスの配列
 */
const std::vector<std::filesystem::path> DefaultTemplateDirs(const std::string& direcotryName) noexcept;

/**
 * @brief 指定のテンプレートファイルを探す
 * @param direcotries 探索するディレクトリの一覧
 * @param filename 指定のファイル名
 * @return 見つけた場合はファイルへのパス、なければ空のパス． 
 */
const std::filesystem::path SearchTemplateFile(const std::vector<std::filesystem::path>& direcotries,const std::string& filename) noexcept;