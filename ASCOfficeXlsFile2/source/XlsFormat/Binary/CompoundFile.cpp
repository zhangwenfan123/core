#include "precompiled_xls.h"
#include "CompoundFile.h"
#include "CFStream.h"
//#include <Exception/CompoundFileFormatError.h>
#include <sstream>

namespace XLS
{;


CompoundFile::~CompoundFile()
{
	streams.clear();

	if (storage_)delete storage_;
	storage_ = NULL;
}

CompoundFile::CompoundFile(const std::wstring & file_path, const ReadWriteMode mode)
:	rwMode(mode)
{
	unsigned int grfMode = 0;

	storage_ = new POLE::Storage(file_path.c_str());
	if (storage_ == NULL) return;

	switch(rwMode)
	{		
		case cf_ReadMode:
		{
			if (storage_->open(false, false) == false)
				throw;
			
		}break;
		case cf_WriteMode:
		{
			if (storage_->open(true, true) == false)
				throw;			
		}break;
	}
}


// Opens "Workbook" stream and returns the only reference
CFStreamPtr CompoundFile::getWorkbookStream()
{
	return getNamedStream("Workbook");
}


// Creates "Workbook" stream and returns the only reference
CFStreamPtr CompoundFile::createWorkbookStream()
{
	return createNamedStream("Workbook");
}


// Opens "SummaryInformation" stream and returns the only reference
CFStreamPtr CompoundFile::getSummaryInformationStream()
{
	return getNamedStream("\005SummaryInformation");
}


// Creates "SummaryInformation" stream and returns the only reference
CFStreamPtr CompoundFile::createSummaryInformationStream()
{
	return createNamedStream("\005SummaryInformation");
}


// Closes "SummaryInformation" stream
void CompoundFile::closeSummaryInformationStream()
{
	return closeNamedStream("\005SummaryInformation");
}


// Opens "SummaryInformation" stream and returns the only reference
CFStreamPtr CompoundFile::getDocumentSummaryInformationStream()
{
	return getNamedStream("\005DocumentSummaryInformation");
}


// Creates "SummaryInformation" stream and returns the only reference
CFStreamPtr CompoundFile::createDocumentSummaryInformationStream()
{
	return createNamedStream("\005DocumentSummaryInformation");
}


// Closes "SummaryInformation" stream
void CompoundFile::closeDocumentSummaryInformationStream()
{
	closeNamedStream("\005DocumentSummaryInformation");
}


CFStreamPtr CompoundFile::getNamedStream(const std::string& name)
{
	if(!streams[name])
	{
		streams[name].reset(new CFStream(openStream(name.c_str())));
	}
	return streams[name];
}


CFStreamPtr CompoundFile::createNamedStream(const std::string& name)
{
	if(!streams[name])
	{
		streams[name].reset(new CFStream(createStream(name.c_str())));
	}
	return streams[name];
}


void CompoundFile::closeNamedStream(const std::string& name)
{
	streams[name].reset();
}


// Opens a stream in the storage (shall be called not more than once per stream)
POLE::Stream* CompoundFile::openStream(const std::string & stream_name)
{
	POLE::Stream* pStream = new POLE::Stream(storage_, stream_name);
	if(pStream == NULL)
	{
		throw;// EXCEPT::RT::CompoundFileFormatError(std::string("Error opening \"") + static_cast<char*>(stream_name) + "\" stream", hres);
	}
	return pStream;
}


// Creates a new stream in the storage
POLE::Stream* CompoundFile::createStream(const std::string & stream_name)
{
	POLE::Stream* pStream = new POLE::Stream(storage_, stream_name, true);
	if(pStream == NULL)
	{
		throw;// EXCEPT::RT::CompoundFileFormatError(std::string("Error creating \"") + static_cast<char*>(stream_name) + "\" stream", hres);
	}
	return pStream;
}


} // namespace XLS


