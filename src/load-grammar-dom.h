#ifndef __RTZassistDom1__
#define __RTZassistDom1__

#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XercesVersion.hpp>
#include <xercesc/util/Xerces_autoconf_config.hpp>

#include <xercesc/dom/DOMLSparser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/dom/DOMLocator.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>

#include <xercesc/validators/common/Grammar.hpp>

#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include <xercesc/framework/XMLGrammarPool.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>


#include <string>
#include <memory>   // std::auto_ptr
#include <cstddef>  // std::size_t
#include <iostream>

#include <wx/filename.h>

int mainValidator(int argc, const char* args[]);

#endif