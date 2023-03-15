#include "AppMainOptions.hpp"

#include<cassert>

using namespace cxxopts;
using namespace std;

namespace AppMain {
    // アプリケーション用のOptionオブジェクトを返す
    const Options CreateAppOptions(const string& name, const string& desc) noexcept {
        auto opt = Options(name, desc).allow_unrecognised_options();
        // 共通の設定
        opt.add_options()
            ("cv,cVer", "CMakeのバージョン", value<string>()->default_value(""))
            ("h,help", "このヘルプを表示する");
        
        // プロジェクト
        opt.add_options("project")
            ("n,name", "プロジェクトの名前．", value<string>()->default_value(""))
            ("v,version", "プロジェクのトバージョン．", value<string>()->default_value("0.0.0"))
            ("l,language", "プロジェクで使用する言語．", value<string>()->default_value("CXX"))
            ("b,buildType", "プロジェクトのビルドタイプ．", value<string>()->default_value("Release"));
        return opt;
    };

    // アプリケーションの引数をパースした結果を返す
    const AppOption ParseOptions(const string& name, const string& desc, const int argc, const char* argv[]) noexcept {
        auto opt = CreateAppOptions(name, desc);
        return opt.parse(argc, argv);
    };
}