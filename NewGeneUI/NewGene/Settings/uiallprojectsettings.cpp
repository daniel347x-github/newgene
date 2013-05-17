#include "uiallprojectsettings.h"

UIAllProjectSettings::UIAllProjectSettings(Messager & messager, QObject * parent)
	: UIAllSettings(messager, parent)
{
	CreateImplementation(messager);
}

UIAllProjectSettings::UIAllProjectSettings(Messager & messager, boost::filesystem::path const path_to_settings, QObject * parent) :
	UIAllSettings(messager, parent)
{
	CreateImplementation(messager, path_to_settings);
}

void UIAllProjectSettings::CreateImplementation(Messager & messager)
{
	__impl.reset(new _impl(messager));
}

void UIAllProjectSettings::CreateImplementation(Messager & messager, boost::filesystem::path const path_to_settings)
{
	__impl.reset(new _impl(messager, path_to_settings));
}

void UIAllProjectSettings::_impl::CreateInternalImplementations(Messager & messager)
{
	__ui_impl.reset(new _UIRelatedImpl(messager));
	__backend_impl.reset(new _BackendRelatedImpl(messager));
}

void UIAllProjectSettings::_impl::CreateInternalImplementations(Messager & messager, boost::filesystem::path const path_to_settings)
{
	__ui_impl.reset(new _UIRelatedImpl(messager, path_to_settings));
	__backend_impl.reset(new _BackendRelatedImpl(messager, path_to_settings));
}
