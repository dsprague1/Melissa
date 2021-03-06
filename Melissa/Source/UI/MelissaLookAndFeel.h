#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "MelissaUISettings.h"
#include "MelissaUtility.h"

static constexpr float lineThickness = 1.4;

class MelissaLookAndFeel : public LookAndFeel_V4
{
public:
    MelissaLookAndFeel()
    {
        setColour(Label::textColourId, Colour::fromFloatRGBA(1.f, 1.f, 1.f, 0.8f));
        setColour(ListBox::outlineColourId, Colour::fromFloatRGBA(1.f, 1.f, 1.f, 0.4f));
        setColour(ListBox::backgroundColourId, Colours::transparentWhite);
        setColour(DirectoryContentsDisplayComponent::highlightColourId, Colour::fromFloatRGBA(1.f, 1.f, 1.f, 0.2f));
    }
    
    virtual ~MelissaLookAndFeel() {};
    
    void setBottomComponent(Component* bottomComponent)
    {
        bottomComponent_ = bottomComponent;
    }
    
    void drawButtonBackground(Graphics& g, Button& b, const Colour &backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        const auto& c = b.getLocalBounds();
        g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, shouldDrawButtonAsHighlighted ? 0.8f : 0.4f));
        g.drawRoundedRectangle(lineThickness / 2, lineThickness / 2, c.getWidth() - lineThickness - 1, c.getHeight() - lineThickness - 1, (c.getHeight() - lineThickness) / 2, lineThickness);
    }
    
    void drawButtonText(Graphics& g, TextButton& tb, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, 0.8f));
        g.setFont(MelissaUISettings::fontSizeMain());
        g.drawText(tb.getButtonText(), 0, 0, tb.getWidth(), tb.getHeight(), Justification::centred);
    }
    
     void drawToggleButton(Graphics& g, ToggleButton& tb, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        const bool b = tb.getToggleState() || shouldDrawButtonAsHighlighted || shouldDrawButtonAsDown;
        const auto& c = tb.getLocalBounds();
        g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, b ? 0.8f : 0.4f));
        g.drawText(tb.getToggleState() ? "On" : "Off", 0, 0, tb.getWidth(), tb.getHeight(), Justification::centred);
        g.setFont(MelissaUISettings::fontSizeMain());
        g.drawRoundedRectangle(lineThickness / 2, lineThickness / 2, c.getWidth() - lineThickness - 1, c.getHeight() - lineThickness - 1, (c.getHeight() - lineThickness) / 2, lineThickness);
    }
    
    void drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s) override
    {
        if (style != Slider::LinearHorizontal) return;
        
        const auto& c = s.getLocalBounds();
        const float xOffset = lineThickness / 2;
        const float yOffset = lineThickness / 2;
        const float w = c.getWidth() - lineThickness - 1;
        const float h = c.getHeight() - lineThickness - 1;
        const float cornerSize = (c.getHeight() - 12 - lineThickness) / 2;
        
        g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, 0.4f));
        g.drawRoundedRectangle(xOffset, yOffset + 6, w, h - 12, cornerSize, lineThickness);
        
        {
            Rectangle<int> rect(xOffset + lineThickness, yOffset + 6 + 1, (sliderPos - 1) - (xOffset + lineThickness) - 4, h - 12 - 2);
            const int r = rect.getHeight();
            const int x0 = rect.getX();
            const int x1 = x0 + r / 2;
            const int x2 = x0 + rect.getWidth() + 2;
            const int y0 = rect.getY() + 1;
            const int y1 = rect.getY() + 1 + rect.getHeight();
            
            //g.setGradientFill(ColourGradient(Colour::fromFloatRGBA(1.f, 1.f, 1.f, 0.4f), x0, (y1 + y0) / 2, Colour::fromFloatRGBA(1.f, 1.f, 1.f, 0.6f), x2 - x0, (y1 + y0) / 2, false));
            g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, 0.4));
            
            Path path;
            path.addArc(x0, y0, r, r, M_PI, 2 * M_PI);
            path.lineTo(x1, y0);
            path.lineTo(x2, y0);
            path.addArc(x2, y0, r, r, 0, M_PI);
            path.lineTo(x2, y1);
            path.lineTo(x1, y1);
            path.closeSubPath();
            g.fillPath(path);
        }
    }
    
    void drawLinearSliderThumb (Graphics &, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider &) override
    {
        
    }
    
    void drawPopupMenuBackground (Graphics& g, int width, int height) override
    {
        g.fillAll(Colour(MelissaUISettings::dialogBackgoundColour()));
    }
    
    void drawPopupMenuItem(Graphics& g, const Rectangle<int>& area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String& text, const String &shortcutKeyText, const Drawable *icon, const Colour *textColour) override
    {
        g.setColour(Colour(MelissaUISettings::dialogBackgoundColour()));
        g.fillRect(area);
        
        if (isHighlighted)
        {
            g.setColour(Colour(MelissaUISettings::mainColour()).withAlpha(0.1f));
            g.fillRect(area.reduced(2, 0));
        }
        
        g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, 0.8f));
        g.setFont(MelissaUISettings::fontSizeSub());
        g.drawText(text, area.reduced(10, 0), Justification::left);
    }
    
    void drawMenuBarBackground (Graphics& g, int width, int height, bool isMouseOverBar, MenuBarComponent &) override
    {
        if (isMouseOverBar)
        {
            g.fillAll(Colour(MelissaUISettings::dialogBackgoundColour()));
        }
        else
        {
            g.fillAll(Colour(MelissaUISettings::mainColour()).withAlpha(0.8f));
        }
    }
    
    Font getTextButtonFont(TextButton& tb, int buttonHeight) override
    {
        return Font(MelissaUISettings::fontSizeMain());
    }
    
    void fillTextEditorBackground(Graphics& g, int width, int height, TextEditor& te) override
    {
        // no background
    }
    
    void drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& te) override
    {
        const auto& c = te.getLocalBounds();
        g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, 0.4f));
        g.drawRoundedRectangle(lineThickness / 2, lineThickness / 2, c.getWidth() - lineThickness - 1, c.getHeight() - lineThickness - 1, (c.getHeight() - lineThickness) / 2, lineThickness);
    }
     
    void drawComboBox(Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& cb) override
    {
        const auto& c = cb.getLocalBounds();
        g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, 0.4f));
        g.drawRoundedRectangle(lineThickness / 2, lineThickness / 2, c.getWidth() - lineThickness - 1, c.getHeight() - lineThickness - 1, (c.getHeight() - lineThickness) / 2, lineThickness);
        
        constexpr int triHeight = 6;
        constexpr int triWidth = 12;
        g.drawLine(width - 10 - triWidth, (height - triHeight) / 2, width - 10 - triWidth / 2, (height + triHeight) / 2, lineThickness);
        g.drawLine(width - 10 - triWidth / 2, (height + triHeight) / 2, width - 10, (height - triHeight) / 2, lineThickness);
    }
    
    Font getComboBoxFont (ComboBox &) override
    {
        return Font(MelissaUISettings::fontSizeMain());
    }
    
    void drawScrollbar(Graphics& g, ScrollBar& scrollbar, int x, int y, int width, int height, bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown) override
    {
        const bool highlight = isMouseOver || isMouseDown;
        
        g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, highlight ? 0.6f : 0.4f));
        
        if (isScrollbarVertical)
        {
            g.fillRoundedRectangle(x, y + thumbStartPosition, width, thumbSize, width / 2);
        }
        else
        {
            g.fillRoundedRectangle(x + thumbStartPosition, y, thumbSize, height, height / 2);
        }
    }
    
    void drawTableHeaderBackground(Graphics& g, TableHeaderComponent& c) override
    {
        g.setColour(Colour(MelissaUISettings::mainColour()).withAlpha(0.1f));
        g.fillAll();
    }
    
    void drawTableHeaderColumn(Graphics& g, TableHeaderComponent&, const String& columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags) override
    {
        g.setColour(Colours::white);
        g.setFont(MelissaUISettings::fontSizeMain());
        g.drawText(columnName, 10, 0, width - 1, height, Justification::left);
    }
    
    void drawFileBrowserRow(Graphics& g, int width, int height,
                            const File&, const String& filename, Image* icon,
                            const String& fileSizeDescription,
                            const String& fileTimeDescription,
                            bool isDirectory, bool isItemSelected,
                            int /*itemIndex*/, DirectoryContentsDisplayComponent& dcc) override
    {
        auto fileListComp = dynamic_cast<Component*> (&dcc);

        if (isItemSelected)
            g.fillAll (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::highlightColourId)
                                               : findColour (DirectoryContentsDisplayComponent::highlightColourId));

        const int x = 32;
        g.setColour (Colours::black);

        if (icon != nullptr && icon->isValid())
        {
            g.drawImageWithin (*icon, 2, 2, x - 4, height - 4,
                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                               false);
        }
        else
        {
            if (auto* d = isDirectory ? getDefaultFolderImage()
                                      : getDefaultDocumentFileImage())
                d->drawWithin (g, Rectangle<float> (2.0f, 2.0f, x - 4.0f, height - 4.0f),
                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
        }

        if (isItemSelected)
            g.setColour (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::highlightedTextColourId)
                                                 : findColour (DirectoryContentsDisplayComponent::highlightedTextColourId));
        else
            g.setColour (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::textColourId)
                                                 : findColour (DirectoryContentsDisplayComponent::textColourId));

        g.setFont(MelissaUISettings::fontSizeMain());
        g.drawFittedText (filename,
                          x, 0, width - x, height,
                          Justification::centredLeft, 1);

    }
    
    Font getPopupMenuFont() override
    {
        return Font(MelissaUISettings::fontSizeMain());
    }
    
    
    Font getMenuBarFont(MenuBarComponent&, int itemIndex, const String& itemText) override
    {
        return Font(MelissaUISettings::fontSizeMain());
    }
    
    
    Button* createFileBrowserGoUpButton() override
    {
        class UpButton : public Button
        {
        public:
            UpButton() : Button("") { }
            
            void paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
            {
                constexpr int lineHeight = 2;
                
                const bool highlighed = shouldDrawButtonAsHighlighted || shouldDrawButtonAsDown;
                g.setColour(Colour(MelissaUISettings::mainColour()).withAlpha(highlighed ? 1.f : 0.6f));
                
                const int w = getWidth();
                const int h = getHeight();
                g.fillRoundedRectangle(0, 0, w, lineHeight, lineHeight / 2);
                g.fillRoundedRectangle(0, (h - lineHeight) / 2, w, lineHeight, lineHeight / 2);
                g.fillRoundedRectangle(0, h - lineHeight, w, lineHeight, lineHeight / 2);
            }
        };

        return new UpButton();
    }
    
    void layoutFileBrowserComponent(FileBrowserComponent &browserComp, DirectoryContentsDisplayComponent *fileListComponent, FilePreviewComponent *previewComp, ComboBox *currentPathBox, TextEditor *filenameBox, Button *goUpButton) override
    {
        const auto w = browserComp.getWidth();
        const auto h = browserComp.getHeight();
        
        const int goUpButtonWidth = 60;
        const int margin = 10;
        const int controlHeight = 30;
        currentPathBox->setBounds(0, 0, w - goUpButtonWidth - margin, controlHeight);
        goUpButton->setBounds(currentPathBox->getRight() + margin, 0, goUpButtonWidth, controlHeight);
        //filenameBox->setBounds(0, h - controlHeight, w, controlHeight);
        
        const int listHeight = h - (controlHeight + margin);
        if (auto listAsComp = dynamic_cast<Component*>(fileListComponent))
        {
            listAsComp->setBounds(0, currentPathBox->getBottom() + margin, w, listHeight);
        }
    }
    
    Rectangle<int> getTooltipBounds(const String& tipText, Point<int> screenPos, Rectangle<int> parentArea) override
    {
        if (bottomComponent_ == nullptr)
        {
            int w, h;
            std::tie(w, h) = MelissaUtility::getStringSize(Font(MelissaUISettings::fontSizeSub()), tipText);
            w += 10;
            h += 4;
            
            return Rectangle<int> (screenPos.x > parentArea.getCentreX() ? screenPos.x - (w + 12) : screenPos.x + 24,
                                   screenPos.y > parentArea.getCentreY() ? screenPos.y - (h + 6)  : screenPos.y + 6,
                                   w, h).constrainedWithin(parentArea);
        }
        else
        {
            return bottomComponent_->getLocalBounds().reduced(20, 0).withWidth(bottomComponent_->getWidth() / 2);
        }
    }
    
    void drawTooltip(Graphics& g, const String& text, int width, int height) override
    {
        Rectangle<int> bounds (width, height);
        
        if (bottomComponent_ == nullptr)
        {
            g.setColour(Colours::white.withAlpha(0.8f));
            g.fillRoundedRectangle(0, 0, width, height, height / 2);
            
            g.setColour(Colours::black/* Colour(MelissaUISettings::dialogBackgoundColour())*/);
            g.fillRoundedRectangle(1, 1, width - 2, height - 2, (height - 2) / 2);
        }
        g.setGradientFill(ColourGradient(Colour(0xFF1A1A1A), 0, height, Colour(0xFF1C222B), width, 0, true));
        g.fillAll();
        g.setColour(Colours::white.withAlpha(0.8f));
        g.setFont(Font(MelissaUISettings::fontSizeSub()));
        g.drawText(text, 0, 0, width, height, (bottomComponent_ == nullptr) ? Justification::centred : Justification::left);
    }
    
private:
    Component* bottomComponent_;
};

class MelissaLookAndFeel_Tab : public LookAndFeel_V4
{
public:
    virtual ~MelissaLookAndFeel_Tab() {};
    
    void drawToggleButton(Graphics& g, ToggleButton& tb, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        float alpha = 0.2f;
        if (tb.getToggleState())
        {
            alpha = 0.8f;
        }
        else if (shouldDrawButtonAsHighlighted || shouldDrawButtonAsDown)
        {
            alpha = 0.6f;
        }
        g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, alpha));
        g.setFont(MelissaUISettings::fontSizeMain());
        g.drawText(tb.getButtonText(), 0, 0, tb.getWidth(), tb.getHeight(), Justification::centred);
        g.fillRect(0, tb.getHeight() - 1, tb.getWidth(), 1);
    }
};

class MelissaLookAndFeel_Memo : public LookAndFeel_V4
{
public:
    virtual ~MelissaLookAndFeel_Memo() {};
    
    void fillTextEditorBackground(Graphics& g, int width, int height, TextEditor& te) override
    {
        // no background
    }
    
    void drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& te) override
    {
        const auto& c = te.getLocalBounds();
        g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, 0.4f));
        g.drawRect(c, lineThickness);
    }
    
    void drawScrollbar(Graphics& g, ScrollBar& scrollbar, int x, int y, int width, int height, bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown) override
    {
        const bool highlight = isMouseOver || isMouseDown;
        
        g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, highlight ? 0.6f : 0.4f));
        
        if (isScrollbarVertical)
        {
            g.fillRoundedRectangle(x, y + thumbStartPosition, width, thumbSize, width / 2);
        }
        else
        {
            g.fillRoundedRectangle(x + thumbStartPosition, y, thumbSize, height, height / 2);
        }
    }
};
