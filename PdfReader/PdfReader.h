﻿#ifndef _PDF_READER_H
#define _PDF_READER_H

#include "Src/ErrorConstants.h"

class IRenderer;
class CFontManager;
class CApplicationFonts;

#ifndef PDFREADER_USE_DYNAMIC_LIBRARY
#define PDFREADER_DECL_EXPORT
#else
#include "../DesktopEditor/common/base_export.h"
#define PDFREADER_DECL_EXPORT Q_DECL_EXPORT
#endif

namespace PdfReader
{
	class PDFDoc;
	class GlobalParams;
	class CFontList;

    class PDFREADER_DECL_EXPORT CPdfReader
	{
	public:

		CPdfReader(CApplicationFonts* pAppFonts);
		~CPdfReader();

		bool         LoadFromFile(const wchar_t* wsSrcPath, const wchar_t* wsOwnerPassword = 0, const wchar_t* wsUserPassword = 0, const wchar_t* wsOptions = 0);
		void         Close();
				     
		EError       GetError();
		double       GetVersion();
		int          GetPermissions();
				   
		int          GetPagesCount();
		void         GetPageSize(int nPageIndex, double* pdWidth, double* pdHeight);
		void         GetPageInfo(int nPageIndex, double* pdWidth, double* pdHeight, double* pdDpiX, double* pdDpiY);
		void         DrawPageOnRenderer(IRenderer* pRenderer, int nPageIndex, bool* pbBreak);
		void         ConvertToRaster(int nPageIndex, const wchar_t* wsDstPath, int nImageType);

		bool         ExtractAllImages(const wchar_t* wsDstPath, const wchar_t* wsPrefix = 0);
		int          GetImagesCount();

		void         SetTempFolder(const wchar_t* wsTempFolder);
		void         SetCMapFolder(const wchar_t* wsCMapFolder);
		CFontManager*GetFontManager();
				     
	private:

		PDFDoc*            m_pPDFDocument;
		GlobalParams*      m_pGlobalParams;
		wchar_t*           m_wsTempFolder;
		wchar_t*           m_wsCMapFolder;
		CApplicationFonts* m_pAppFonts;
		CFontManager*      m_pFontManager;
		CFontList*         m_pFontList;
	};
}

#endif // _PDF_READER_H
