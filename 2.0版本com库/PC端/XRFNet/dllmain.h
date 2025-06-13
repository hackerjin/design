// dllmain.h : Declaration of module class.

class CXRFNetModule : public CAtlDllModuleT< CXRFNetModule >
{
public :
	DECLARE_LIBID(LIBID_XRFNetLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_XRFNET, "{5074C0A5-B4EF-4E9F-9E12-09FC56EA79EC}")
};

extern class CXRFNetModule _AtlModule;

