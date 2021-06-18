/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** Asset
*/

#include <filesystem>
#include "EngineExceptions.hpp"
#include "Asset.hpp"

Asset::Asset(std::string name, uint32_t id)
    : _name(name), _entityID(id)
{
    std::string file;

    std::cout << "Creating asset name " << name << std::endl;

    if (std::filesystem::exists("../assets/"))
    {
        for (auto& element : std::filesystem::recursive_directory_iterator("../assets/")) {
            if (!element.is_regular_file())
                continue;
            file = element.path().string();
            if (file.find(name) != std::string::npos) {
                if (file.find("model") != std::string::npos && !_model) {
                    _model = std::make_unique<RayLib::Model>(file);
                } else if (file.find("anim") != std::string::npos) {
                    _animations.insert(std::pair<std::string, RayLib::ModelAnimation>(getAnimationName(file), RayLib::ModelAnimation(file)));
                } else if (file.find("texture") != std::string::npos && !_texture) {
                    _texture = std::make_unique<RayLib::Texture>(file);
                } else if (file.find("sound") != std::string::npos) {
                    _sounds.insert(std::pair<std::string, RayLib::Sound>(getAnimationName(file), RayLib::Sound(file)));
                }
            }
        }
    }

    if (!_model)
        _model = std::make_unique<RayLib::Model>();
    if (!_texture)
        _texture = std::make_unique<RayLib::Texture>();

    //if (_animations.size() == 0 && _model == nullptr && _texture == nullptr)
    //    throw ECS::Exception::AssetException("Cannot find any asset for \"" + name + "\".");

    _model->SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, *_texture.get());
    std::cout << "Done asset name " << name << std::endl;
}

Asset::Asset(Asset &other)
    : _animations(), _model(std::make_unique<RayLib::Model>(other.getModel().GetFileName())), _texture(std::make_unique<RayLib::Texture>(other.getTexture().GetFileName())), _name(other.getName())
{
    for (auto &animation : other.getAnimations())
        this->_animations.emplace(animation.first, animation.second);
}

Asset::~Asset()
{
}

Asset& Asset::operator=(Asset& other)
{
    this->_name = other.getName();
    this->_model = std::make_unique<RayLib::Model>(other.getModel().GetFileName());
    this->_texture = std::make_unique<RayLib::Texture>(other.getTexture().GetFileName());
    this->_animations.clear();
    for (auto &animation : other.getAnimations())
        this->_animations.emplace(animation.first, animation.second);
    return (*this);
}

// !nomenclature: assetname_anim_idle.iqm
std::string Asset::getAnimationName(const std::string &filePath)
{
    std::string name = getFileNameWithoutExt(filePath);
    std::size_t separatorIdx = name.find_last_of("_");

    if (separatorIdx == std::string::npos)
        return ("unknown");
    std::cout << "Creating animation with state" << name.substr(separatorIdx + 1, std::string::npos) << std::endl;
    return (name.substr(separatorIdx + 1, std::string::npos));
}

std::string Asset::getFileNameWithoutExt(const std::string &filePath)
{
    size_t lastFolder = filePath.find_last_of("/");
    size_t extDot = filePath.find_last_of(".");

    if (extDot == std::string::npos && lastFolder == std::string::npos)
        return filePath;
    else if (extDot == std::string::npos)
        return filePath.substr(lastFolder + 1, std::string::npos);
    else if (lastFolder == std::string::npos)
        return filePath.substr(0, extDot - 1);
    return filePath.substr(lastFolder + 1, extDot - lastFolder - 1);
}

const std::string &Asset::getName() const
{
    return (_name);
}

RayLib::Texture &Asset::getTexture()
{
    return (*_texture.get());
}

RayLib::Model &Asset::getModel()
{
    return (*_model.get());
}

std::map<std::string, RayLib::ModelAnimation> &Asset::getAnimations()
{
    return (_animations);
}

std::map<std::string, RayLib::Sound> &Asset::getSounds()
{
    return (_sounds);
}

uint32_t Asset::getID(void)
{
    return (_entityID);
}

