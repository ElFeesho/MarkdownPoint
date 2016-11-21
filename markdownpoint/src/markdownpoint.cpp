#include <iostream>

#include <markdownpoint.hpp>

#include <hpdf.h>

#include <stdexcept>

namespace MarkdownPoint
{
	Presentation::Presentation() {
		HPDF_Doc doc = HPDF_New([](HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
			std::cerr << "Error occurred (" << error_no << ", " << detail_no << ")" << std::endl;
		}, nullptr);

		if (HPDF_NewDoc(doc) != HPDF_OK)
		{
			throw std::domain_error("Failed to create new PDF document");
		}

		HPDF_Page page = HPDF_AddPage(doc);

		HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
		HPDF_Page_SetRGBFill(page, 0.3, 0.3, 0.3);

		HPDF_Page_Rectangle(page, 0, 0, HPDF_Page_GetWidth(page), HPDF_Page_GetHeight(page));

		HPDF_Page_Fill(page);
	    
	    HPDF_Font font = HPDF_GetFont(doc, "Helvetica", NULL);
		HPDF_Page_SetFontAndSize(page, font, 48);
		
		HPDF_Page_SetRGBFill(page, 0.8, 0.8, 0.8);
		float tw = HPDF_Page_TextWidth(page, "Heading");
		HPDF_Page_BeginText(page);
		HPDF_Page_TextOut(page, (HPDF_Page_GetWidth(page) - tw) / 2, HPDF_Page_GetHeight (page) - 50, "Heading");
		HPDF_Page_EndText (page);

		HPDF_SaveToFile(doc, "test.pdf");

		HPDF_FreeDocAll(doc);
	}
}