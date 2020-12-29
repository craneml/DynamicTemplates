//
// $Id: twoPagePerDayDrawDay.cpp,v 1.9 2010/01/01 20:22:33 igor Exp $
//
// This file is part of DIY_Dynamic_Templates_V2
// 
// DIY_Dynamic_Templates_V2 is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// DIY_Dynamic_Templates_V2 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// Refer to the GNU General Public License in file "license.txt"
// Otherwise, see <http://www.gnu.org/licenses/>.


#include <QPrinter>
#include <QPainter>
#include <QLinearGradient>
#include <QLineF>
#include <QTime>
#include <QFont>
#include <QFontDatabase>
#include <math.h>

#include <QtDebug>  // this is here for debugging 
#include "RenderArea.h"

//
// Commented out code is from me debugging why I can't create a QFont other than Helvetica
//

//bool isFixedPitch(const QFont &font) {
//    qDebug() << font;
//   const QFontInfo fi(font);
//   qDebug() << fi.family() << fi.fixedPitch();
//   return fi.fixedPitch();
//}

//QFont getMonospaceFont() {
//   QFont font("monospace");
//   if (isFixedPitch(font)) return font;
//   font.setStyleHint(QFont::Monospace);
//   if (isFixedPitch(font)) return font;
//   font.setStyleHint(QFont::TypeWriter);
//   if (isFixedPitch(font)) return font;
//   font.setFamily("courier");
//   if (isFixedPitch(font)) return font;
//   return font;
//}

void RenderArea::twoPagePerDayDrawDay ( QPainter* painter, bool leftPage )
{
	int loop ;
	qreal howManyTall ;
	qreal howManyFromTop ;

//    int id = QFontDatabase::addApplicationFont("://fonts/Envy Code R.ttf");
//    qDebug() << id;
//    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
//    qDebug() << family;
//    QFont werdz(family);
//    QFont werdz("://fonts/Envy Code R.ttf");
//    qDebug() << werdz.rawName();
//    qDebug() << werdz.family();
//    qDebug() << werdz.defaultFamily();
//    qDebug() << werdz.toString();

    // Font for words
    QFont werdz ("Times New Roman");
    qDebug() << werdz;
    const QFontInfo fi(werdz);
    qDebug() << fi.family() << fi.fixedPitch() << fi.styleName() << fi.styleHint();

    // At least customize Helvetica a little to make it more palatable
    werdz.setCapitalization(QFont::SmallCaps);

//    qDebug() << werdz;
//    isFixedPitch(werdz);

//    const QStringList familyNames = QFontDatabase::applicationFontFamilies( id );
//    for( auto familyName :  familyNames )
//    {
//        qDebug("XXX");
//        qDebug() << familyName;
//    }

    // Font for days
    QFont dayz ( "Roboto Mono" ) ;
	
	QPen thePen(Qt::white, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::SolidPattern ) ;

	QRectF paper = thePaper ;
	
	QRectF page ;
	
	if ( leftPage )
	{	page = thePage ;
	}
	else
	{	page = QRectF
		(	thePaper.width() - thePage.width() - thePage.x(),
			thePage.y(),
			thePage.width(),
			thePage.height()
		) ;
	}

	howManyTall = floor ( page.height() / displayLineSpacing ) ;
	howManyFromTop = ceil ( (page.height() / 4.0 ) / displayLineSpacing ) ;

	// --- "erase" the page ------------------------------------------------------
	painter->setBrush ( theBrush  ) ;
	painter->setPen ( thePen ) ;
	painter->drawRect ( paper ) ;

	thePen.setColor ( lineColors[0] ) ;
	theBrush.setColor ( lineColors[0] ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	
	//-------- Page Top Title ----------------------------------------------------
	
	QRectF justAbox ( page.x(), page.y(), 63. * page.width() / 128., page.height() / 4. ) ;
	QRectF justAbox2 = justAbox ;
	justAbox2.setWidth ( justAbox.width() / 2 ) ; 
	
	if ( !leftPage )
	{	justAbox2.moveRight ( page.right() ) ;
		justAbox.moveRight ( page.right() ) ;
	}

	//-------- Page Top Title ----------------------------------------------------
	//
	//-------- big day number ----------------------------------------------------
    painter->setFont ( dayz ) ; // dayz
	
	QRectF textRect = justAbox2 ;
	textRect.setHeight ( justAbox.height() / 3. ) ;

	if ( leftPage )
	{	fitStringInRect ( textRect, today.toString ( "d" ), painter, Qt::AlignTop | Qt::AlignLeft, 0.90 ) ;
	}
	else
	{	fitStringInRect ( textRect, today.toString ( "d" ), painter, Qt::AlignTop | Qt::AlignRight, 0.90 ) ;
	}
	
	//-------- day of the week ----------------------------------------------------
    painter->setFont ( werdz ) ; // werdz

	textRect.moveTop( textRect.bottom() ) ;
	textRect.setHeight ( 6.0 * textRect.height() / 15.0 ) ;

	thePen.setColor ( lineColors[0] ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	
	if ( leftPage )
    {	fitStringInRect ( textRect, today.toString ( "MMM yyyy" ), painter, Qt::AlignVCenter | Qt::AlignLeft, 0.90 ) ;
	}
	else
    {	fitStringInRect ( textRect, today.toString ( "MMM yyyy" ), painter, Qt::AlignVCenter | Qt::AlignRight, 0.90 ) ;
	}
	//-------- month and year ----------------------------------------------------
	textRect.moveTop( textRect.bottom() ) ;
	textRect.setHeight ( 3.0 * textRect.height() / 2.0 ) ;

	if ( leftPage )
    {	fitStringInRect ( textRect, today.toString ( "ddd" ), painter, Qt::AlignVCenter | Qt::AlignLeft, 0.90 ) ;
	}
	else
    {	fitStringInRect ( textRect, today.toString ( "ddd" ), painter, Qt::AlignVCenter | Qt::AlignRight, 0.90 ) ;
	}
	

	//-------- current month ----------------------------------------------------
	if ( leftPage )
	{	justAbox2.moveLeft ( justAbox2.right() ) ;
	}
	else
	{	justAbox2.moveRight ( justAbox2.left() ) ;
	}
	justAbox2.setHeight ( 2 * justAbox2.height() / 3 ) ;
	
	drawLittleMonth ( painter, today, justAbox2, true )  ;

	//-------- month before ----------------------------------------------------
//	justAbox2.moveTop ( justAbox2.bottom() ) ;
//	justAbox2.setHeight ( justAbox2.height() / 2 ) ;
//	justAbox2.setWidth ( justAbox2.width() / 2 ) ;
	
//	drawLittleMonth
//	(	painter,
//		today.addMonths ( -1 ),
//		QRectF
//		(	justAbox2.x(),
//			justAbox2.y(),
//			31 * justAbox2.width() / 32,
//			justAbox2.height()
//		),
//		false
//	)  ;

	//-------- month after ----------------------------------------------------
//	justAbox2.moveLeft ( justAbox2.right() ) ;
	
//	drawLittleMonth
//	(	painter,
//		today.addMonths ( 1 ),
//		QRectF
//		(	justAbox2.x() + (justAbox2.width() / 32),
//			justAbox2.y(),
//			31 * justAbox2.width() / 32,
//			justAbox2.height()
//		),
//		false
//	)  ;

	//--------------------------------------------------------------------------
	
	int howManyLines = ((int)(howManyTall - howManyFromTop)) - 4 ;
	int howManyTaskLines = 5 * howManyLines / 6 ;
		
	justAbox.setBottom ( howManyTall * displayLineSpacing ) ;
	justAbox.setTop ( justAbox.top() + ( howManyFromTop * displayLineSpacing ) ) ;
	
	QRectF barRect ( justAbox.x(), justAbox.y(), justAbox.width(), displayLineSpacing ) ;
	
    drawSubHeader ( painter, barRect, 0.45, tr("Todos") ) ; // was Daily Tasks

	barRect.moveTop ( barRect.bottom() + ( 0.50 * barRect.height() ) ) ;
	
	for ( loop = 0 ; loop < howManyTaskLines ; loop++ )
	{	drawRow ( painter, barRect, ROW_GREY_STRIPE, true ) ;
		barRect.moveTop ( barRect.bottom() ) ;
	} // while ( barRect.bottom() < page.bottom() ) ;

	barRect.moveTop ( barRect.bottom() - ( 0.50 * barRect.height() ) ) ;
    drawSubHeader ( painter, barRect, 0.45, tr("Meals") ) ; // was Expenses
	barRect.moveTop ( barRect.bottom() + ( 0.50 * barRect.height() ) ) ;

	do
	{	drawRow ( painter, barRect, ROW_GREY_TWO_STRIPE, false ) ;
		barRect.moveTop ( barRect.bottom() ) ;
	} while ( barRect.bottom() < page.bottom() ) ;
	
	//--------------------------------------------------------------------------

	barRect.moveTop ( page.top() ) ;
	
	if ( leftPage )
	{	barRect.moveRight ( page.right() ) ;
	}
	else
	{	barRect.moveLeft ( page.left() ) ;
	}

    drawSubHeader ( painter, barRect, 0.55, tr("Schedule") ) ; // was Appointments
	barRect.moveTop ( barRect.bottom() + ( 0.50 * barRect.height() ) ) ;
	
	thePen.setColor ( lineColors[2] ) ;
	painter->setPen ( thePen ) ;

	int howManyAppointmentLines = (int)(( page.bottom() - barRect.top() ) / displayLineSpacing ) ;
	int blokCount = howManyAppointmentLines / 2 ;
	
	if ( blokCount > 12 ) blokCount = 12 ;
	
	QTime apptHour = firstAppt ;
	
	barRect.setHeight ( 2.0 * displayLineSpacing ) ;

	drawAppointmentRow ( painter, barRect, APPT_BOX_DOUBLE, QString() ) ;
	barRect.moveTop ( barRect.bottom() ) ;
	
	for ( loop = 1 ; loop < (blokCount - 1) ; loop++ ) 
	{	barRect.setHeight ( 2.0 * displayLineSpacing ) ;
		switch  ( clockType )
		{	case 1: // 12 hour clock	
				drawAppointmentRow ( painter, barRect, APPT_BOX_DOUBLE, apptHour.toString("h a").section(' ', 0, 0) ) ;
				break ;
			case 2: // 24 hour clock	
				drawAppointmentRow ( painter, barRect, APPT_BOX_DOUBLE, apptHour.toString("H") ) ;
				break ;
			default:
				drawAppointmentRow ( painter, barRect, APPT_BOX_DOUBLE, QString() ) ;
		}

		apptHour = apptHour.addSecs ( 3600 ) ;
		barRect.moveTop ( barRect.bottom() ) ;
	}
	
	drawAppointmentRow ( painter, barRect, APPT_BOX_DOUBLE, QString() ) ; 
	barRect.moveTop ( barRect.bottom() ) ;

	barRect.setHeight ( displayLineSpacing ) ;
	barRect.moveTop ( barRect.bottom() ) ;

	while ( barRect.bottom() < page.bottom() ) 
	{	drawAppointmentRow ( painter, barRect, APPT_BOX_ZERO, QString() ) ; 
		barRect.moveTop ( barRect.bottom() ) ;
	}
	
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
}	
