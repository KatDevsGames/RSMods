#include "ExtendedRangeMode.h"

cERMode ERMode;

uintptr_t GetStringColor(uintptr_t stringnum, string_state state) {
	uintptr_t edx = stringnum;
	uintptr_t eax = 0;
	uintptr_t magic1 = Offsets.ptr_stringColor;

	uintptr_t ecx = MemUtil.ReadPtr(magic1);

	if (!ecx)
		return NULL;

	eax = MemUtil.ReadPtr(ecx + eax * 0x4 + 0x348);

	if (eax >= 2) {
		return NULL;
	}

	eax = eax * 0xA8;
	eax += edx;

	eax = MemUtil.ReadPtr(ecx + eax * 0x4 + state);

	return eax;
}

struct String { //maybe do sth with this
	uintptr_t strPtr;
	Color oldColor;

	void Init(int strNum, string_state state) {
		strPtr = GetStringColor(strNum, state);
	}

	void SetColor(int stringIdx, float R, float G, float B) {
		if (stringIdx < 0 || stringIdx > 6) {
			std::cout << "wat doink" << std::endl;
			return;
		}

		Color c;
		c.r = R;
		c.g = G;
		c.b = B;

		*(Color*)strPtr = c;
	}

};

/*
  <property
	type="AssocColor"
	name="GuitarStringsEnabledDefault"
	id="3307419348" source="GameColorManager">
	<set index="0" value="1, 0.3098039, 0.3529412" />
	<set index="1" value="0.8862745, 0.7568628, 0.007843138" />
	<set index="2" value="0.1137255, 0.6745098, 0.9764706" />
	<set index="3" value="1, 0.572549, 0.08627451" />
	<set index="4" value="0.2470588, 0.8, 0.04705882" />
	<set index="5" value="0.7843137, 0.145098, 0.9294118" />
  </property>
  <property
	type="AssocColor"
	name="GuitarStringsEnabledColorBlind"
	id="237528906" source="GameColorManager">
	<set index="0" value="0, 0.7764706, 0.5568628" />
	<set index="1" value="1, 0.3098039, 0.3529412" />
	<set index="2" value="0.8862745, 0.7568628, 0.007843138" />
	<set index="3" value="0.1137255, 0.6745098, 0.9764706" />
	<set index="4" value="1, 0.572549, 0.08627451" />
	<set index="5" value="0.2470588, 0.8, 0.04705882" />
  </property>
 */


Color cN;
Color cD;
Color cH;
Color cAmb;
Color cEnabled;
Color cPegTune;
Color cPegInTune;
Color cTextNew;
Color cPart;
Color cBodyNorm;
Color cBodyAcc;
Color cBodyPrev;


std::vector<String> strings;
void cERMode::Toggle7StringMode() { //TODO: use the GUI to make DDS files and load settings here for matching string colors
	// return;
	strings.clear();
	std::vector<Color> oldColors;

	static bool colorsSaved = false;
	uintptr_t string0n = GetStringColor(0, normal); uintptr_t string1n = GetStringColor(1, normal); uintptr_t string2n = GetStringColor(2, normal); uintptr_t string3n = GetStringColor(3, normal); uintptr_t string4n = GetStringColor(4, normal); uintptr_t string5n = GetStringColor(5, normal);
	uintptr_t string0h = GetStringColor(0, highlight); uintptr_t string1h = GetStringColor(1, highlight); uintptr_t string2h = GetStringColor(2, highlight); uintptr_t string3h = GetStringColor(3, highlight); uintptr_t string4h = GetStringColor(4, highlight); uintptr_t string5h = GetStringColor(5, highlight); // highlight = "glow" in gamecolormanager.flat file
	uintptr_t string0d = GetStringColor(0, disabled); uintptr_t string1d = GetStringColor(1, disabled); uintptr_t string2d = GetStringColor(2, disabled); uintptr_t string3d = GetStringColor(3, disabled); uintptr_t string4d = GetStringColor(4, disabled); uintptr_t string5d = GetStringColor(5, disabled); // name="GuitarStringsDisabledColorBlind" id="4184626561"
	 /*//commented out for now as memory addresses are not defined in structs.h
	uintptr_t string0Amb = GetStringColor(0, Ambient); uintptr_t string1Amb = GetStringColor(1, Ambient); uintptr_t string2Amb = GetStringColor(2, Ambient); uintptr_t string3Amb = GetStringColor(3, Ambient); uintptr_t string4Amb = GetStringColor(4, Ambient); uintptr_t string5Amb = GetStringColor(5, Ambient);
	uintptr_t string0Enabled = GetStringColor(0, Enabled); uintptr_t string1Enabled = GetStringColor(1, Enabled); uintptr_t string2Enabled = GetStringColor(2, Enabled); uintptr_t string3Enabled = GetStringColor(3, Enabled); uintptr_t string4Enabled = GetStringColor(4, Enabled); uintptr_t string5Enabled = GetStringColor(5, Enabled);
	uintptr_t string0PegTune = GetStringColor(0, PegTune); uintptr_t string1PegTune = GetStringColor(1, PegTune); uintptr_t string2PegTune = GetStringColor(2, PegTune); uintptr_t string3PegTune = GetStringColor(3, PegTune); uintptr_t string4PegTune = GetStringColor(4, PegTune); uintptr_t string5PegTune = GetStringColor(5, PegTune);
	uintptr_t string0PegInTune = GetStringColor(0, PegInTune); uintptr_t string1PegInTune = GetStringColor(1, PegInTune); uintptr_t string2PegInTune = GetStringColor(2, PegInTune); uintptr_t string3PegInTune = GetStringColor(3, PegInTune); uintptr_t string4PegInTune = GetStringColor(4, PegInTune); uintptr_t string5PegInTune = GetStringColor(5, PegInTune);
	uintptr_t string0Text = GetStringColor(0, text); uintptr_t string1TextNew = GetStringColor(1, text); uintptr_t string2TextNew = GetStringColor(2, text); uintptr_t string3TextNew = GetStringColor(3, text); uintptr_t string4TextNew = GetStringColor(4, text); uintptr_t string5TextNew = GetStringColor(5, text);
	uintptr_t string0Part = GetStringColor(0, Particles); uintptr_t string1Part = GetStringColor(1, Particles); uintptr_t string2Part = GetStringColor(2, Particles); uintptr_t string3Part = GetStringColor(3, Particles); uintptr_t string4Part = GetStringColor(4, Particles); uintptr_t string5Part = GetStringColor(5, Particles);
	uintptr_t string0BodyNorm = GetStringColor(0, BodyNorm); uintptr_t string1BodyNorm = GetStringColor(1, BodyNorm); uintptr_t string2BodyNorm = GetStringColor(2, BodyNorm); uintptr_t string3BodyNorm = GetStringColor(3, BodyNorm); uintptr_t string4BodyNorm = GetStringColor(4, BodyNorm); uintptr_t string5BodyNorm = GetStringColor(5, BodyNorm);
	uintptr_t string0BodyAcc = GetStringColor(0, BodyAcc); uintptr_t string1BodyAcc = GetStringColor(1, BodyAcc); uintptr_t string2BodyAcc = GetStringColor(2, BodyAcc); uintptr_t string3BodyAcc = GetStringColor(3, BodyAcc); uintptr_t string4BodyAcc = GetStringColor(4, BodyAcc); uintptr_t string5BodyAcc = GetStringColor(5, BodyAcc);
	uintptr_t string0BodyPrev = GetStringColor(0, BodyPrev); uintptr_t string1BodyPrev = GetStringColor(1, BodyPrev); uintptr_t string2BodyPrev = GetStringColor(2, BodyPrev); uintptr_t string3BodyPrev = GetStringColor(3, BodyPrev); uintptr_t string4BodyPrev = GetStringColor(4, BodyPrev); uintptr_t string5BodyPrev = GetStringColor(5, BodyPrev);
	*/
	if (!colorsSaved && MemHelpers.GetCurrentMenu() == "LearnASong_Game") {
		cN = *(Color*)string0n;
		cD = *(Color*)string0d;
		cH = *(Color*)string0h;
		/* // this comment block can be removed once the memory spaces are identified in structs.h - I think
		cAmb = *(Color*)string0Amb;
		cEnabled = *(Color*)string0Enabled;
		cPegTune = *(Color*)string0PegTune;
		cPegInTune = *(Color*)string0PegInTune;
		cTextNew = *(Color*)string0Text;
		cPart = *(Color*)string0Part;
		cBodyNorm = *(Color*)string0BodyNorm;
		cBodyAcc = *(Color*)string0BodyAcc;
		cBodyPrev = *(Color*)string0BodyPrev;
		*/

	}

	if(MemHelpers.IsExtendedRangeSong()){
		// Zags custom low B color values manually entered; normal
		Color c0nNew; Color c1nNew; Color c2nNew; Color c3nNew; Color c4nNew; Color c5nNew; 
		c0nNew.r = 0.0; c0nNew.g = 0.7764706; c0nNew.b = 0.5568628;
		c1nNew.r = 0.7490196; c1nNew.g = 0.372549; c1nNew.b = 0.372549;
		c2nNew.r = 0.7490196; c2nNew.g = 0.7176471; c2nNew.b = 0.372549;
		c3nNew.r = 0.3686275; c3nNew.g = 0.6156863; c3nNew.b = 0.7372549;
		c4nNew.r = 0.7490196; c4nNew.g = 0.5529412; c4nNew.b = 0.372549;
		c5nNew.r = 0.372549; c5nNew.g = 0.7490196; c5nNew.b = 0.5921569;
		*(Color*)string0n = c0nNew; *(Color*)string1n = c1nNew;	*(Color*)string2n = c2nNew;	*(Color*)string3n = c3nNew;	*(Color*)string4n = c4nNew;	*(Color*)string5n = c5nNew;

		// Zags custom low B color values manually entered; highlighted
		Color c0hNew; Color c1hNew; Color c2hNew; Color c3hNew; Color c4hNew; Color c5hNew; 
		c0hNew.r = 0.0; c0hNew.g = 1; c0hNew.b = 0.6470588;
		c1hNew.r = 1; c1hNew.g = 0; c1hNew.b = 0.0627451;
		c2hNew.r = 1; c2hNew.g = 0.7803922; c2hNew.b = 0;
		c3hNew.r = 0; c3hNew.g = 0.6627451; c3hNew.b = 1;
		c4hNew.r = 1; c4hNew.g = 0.4470588; c4hNew.b = 0;
		c5hNew.r = 0.2627451; c5hNew.g = 1; c5hNew.b = 0;
		*(Color*)string0h = c0hNew; *(Color*)string1h = c1hNew;	*(Color*)string2h = c2hNew;	*(Color*)string3h = c3hNew;	*(Color*)string4h = c4hNew;	*(Color*)string5h = c5hNew;
		
		// Zags custom low B color values manually entered; disabled
		Color c0dNew; Color c1dNew; Color c2dNew; Color c3dNew; Color c4dNew; Color c5dNew; 
		c0dNew.r = 0.0;	c0dNew.g = 0.2980392; c0dNew.b = 0.2117647;
		c1dNew.r = 0.2980392; c1dNew.g = 0.09019608; c1dNew.b = 0.1058824;
		c2dNew.r = 0.2980392; c2dNew.g = 0.254902; c2dNew.b = 0;
		c3dNew.r = 0.03529412; c3dNew.g = 0.2117647; c3dNew.b = 0.2980392;
		c4dNew.r = 0.2980392; c4dNew.g = 0.1647059; c4dNew.b = 0.02352941;
		c5dNew.r = 0.09019608; c5dNew.g = 0.2980392; c5dNew.b = 0.01568628;
		*(Color*)string0d = c0dNew; *(Color*)string1d = c1dNew;	*(Color*)string2d = c2dNew;	*(Color*)string3d = c3dNew;	*(Color*)string4d = c4dNew;	*(Color*)string5d = c5dNew;

		//keyboard monkey; The values below need to be called some how - I'm too stupid to work out how to make them be where they should be.... help please? ZZ
		//first line of each block should (I think) be moved up to around line #94 etc. 
		//Proerties and ID from the GameColorManager.FLat files are included for refference.
		/*
		//name = "GuitarStringsAmbientColorBlind" id = "3175458924" source = "GameColorManager" >
		//uintptr_t string0Amb = GetStringColor(0, Ambient); uintptr_t string1Amb = GetStringColor(1, Ambient); uintptr_t string2Amb = GetStringColor(2, Ambient); uintptr_t string3Amb = GetStringColor(3, Ambient); uintptr_t string4Amb = GetStringColor(4, Ambient); uintptr_t string5Amb = GetStringColor(5, Ambient);

		Color c0AmbNew; Color c1AmbNew; Color c2AmbNew; Color c3AmbNew; Color c4AmbNew; Color c5AmbNew;
		c0AmbNew.r = 0.372549; c0AmbNew.g = 0.7490196; c0AmbNew.b = 0.6431373;
		c1AmbNew.r = 0.7490196; c1AmbNew.g = 0.372549; c1AmbNew.b = 0.372549;
		c2AmbNew.r = 0.7490196; c2AmbNew.g = 0.7176471; c2AmbNew.b = 0.372549;
		c3AmbNew.r = 0.3686275; c3AmbNew.g = 0.6156863; c3AmbNew.b = 0.7372549;
		c4AmbNew.r = 0.7490196; c4AmbNew.g = 0.5529412; c4AmbNew.b = 0.372549;
		c5AmbNew.r = 0.372549; c5AmbNew.g = 0.7490196; c5AmbNew.b = 0.5921569;
		*(Color*)string0Amb = c0AmbNew; *(Color*)string1Amb = c1AmbNew;	*(Color*)string2Amb = c2AmbNew;	*(Color*)string3Amb = c3AmbNew;	*(Color*)string4Amb = c4AmbNew;	*(Color*)string5Amb = c5AmbNew;
		

		//name="GuitarStringsEnabledColorBlind" id="237528906"
		//uintptr_t string0Enabled = GetStringColor(0, Enabled); uintptr_t string1Enabled = GetStringColor(1, Enabled); uintptr_t string2Enabled = GetStringColor(2, Enabled); uintptr_t string3Enabled = GetStringColor(3, Enabled); uintptr_t string4Enabled = GetStringColor(4, Enabled); uintptr_t string5Enabled = GetStringColor(5, Enabled);
		
		Color c0StrEnaNew; Color c1StrEnaNew; Color c2StrEnaNew; Color c3StrEnaNew; Color c4StrEnaNew; Color c5StrEnaNew;
		c0StrEnaNew.r = 0; c0StrEnaNew.g = 0.7764706; c0StrEnaNew.b = 0.5568628;
		c1StrEnaNew.r = 1; c1StrEnaNew.g = 0.3098039; c1StrEnaNew.b = 0.3529412;
		c2StrEnaNew.r = 0.8862745; c2StrEnaNew.g = 0.7568628; c2StrEnaNew.b = 0.007843138;
		c3StrEnaNew.r = 0.1137255; c3StrEnaNew.g = 0.6745098; c3StrEnaNew.b = 0.9764706;
		c4StrEnaNew.r = 1; c4StrEnaNew.g = 0.572549; c4StrEnaNew.b = 0.08627451;
		c5StrEnaNew.r = 0.2470588; c5StrEnaNew.g = 0.8; c5StrEnaNew.b = 0.04705882;
		*(Color*)string0Enabled = c0StrEnaNew; *(Color*)string1Enabled = c1StrEnaNew;	*(Color*)string2Enabled = c2StrEnaNew;	*(Color*)string3Enabled = c3StrEnaNew;	*(Color*)string4Enabled = c4StrEnaNew;	*(Color*)string5Enabled = c5StrEnaNew;
		

		 //name="GuitarPegsTuningBlind" id="1806691030"
		//uintptr_t string0PegTune = GetStringColor(0, PegTune); uintptr_t string1PegTune = GetStringColor(1, PegTune); uintptr_t string2PegTune = GetStringColor(2, PegTune); uintptr_t string3PegTune = GetStringColor(3, PegTune); uintptr_t string4PegTune = GetStringColor(4, PegTune); uintptr_t string5PegTune = GetStringColor(5, PegTune);

		Color c0PegTuneNew; Color c1PegTuneNew; Color c2PegTuneNew; Color c3PegTuneNew; Color c4PegTuneNew; Color c5PegTuneNew;
		c0PegTuneNew.r = 0.003921569; c0PegTuneNew.g = 0.6; c0PegTuneNew.b = 0.4117647;
		c1PegTuneNew.r = 0.7490196; c1PegTuneNew.g = 0; c1PegTuneNew.b = 0.05882353;
		c2PegTuneNew.r = 0.6862745; c2PegTuneNew.g = 0.4588235; c2PegTuneNew.b = 0;
		c3PegTuneNew.r = 0; c3PegTuneNew.g = 0.3764706; c3PegTuneNew.b = 0.7294118;
		c4PegTuneNew.r = 0.6980392; c4PegTuneNew.g = 0.2196078; c4PegTuneNew.b = 0;
		c5PegTuneNew.r = 0.1254902; c5PegTuneNew.g = 0.5490196; c5PegTuneNew.b = 0;
		*(Color*)string0PegTune = c0PegTuneNew; *(Color*)string1PegTune = c1PegTuneNew;	*(Color*)string2PegTune = c2PegTuneNew;	*(Color*)string3PegTune = c3PegTuneNew;	*(Color*)string4PegTune = c4PegTuneNew;	*(Color*)string5PegTune = c5PegTuneNew;
		

		 //name="GuitarPegsInTuneBlind" id="2547441015"
		//uintptr_t string0pegintune = GetStringColor(0, pegintune); uintptr_t string1pegintune = GetStringColor(1, pegintune); uintptr_t string2pegintune = GetStringColor(2, pegintune); uintptr_t string3pegintune = GetStringColor(3, pegintune); uintptr_t string4pegintune = GetStringColor(4, pegintune); uintptr_t string5pegintune = GetStringColor(5, pegintune);
		
		Color c0PegInTuneNew; Color c1PegInTuneNew; Color c2PegInTuneNew; Color c3PegInTuneNew; Color c4PegInTuneNew; Color c5PegInTuneNew; 
		c0PegInTuneNew.r = 0; c0PegInTuneNew.g = 0.6980392; c0PegInTuneNew.b = 0.4745098;
		c1PegInTuneNew.r = 0.6980392; c1PegInTuneNew.g = 0; c1PegInTuneNew.b = 0.05490196;
		c2PegInTuneNew.r = 0.6980392; c2PegInTuneNew.g = 0.5568628; c2PegInTuneNew.b = 0;
		c3PegInTuneNew.r = 0; c3PegInTuneNew.g = 0.4627451; c3PegInTuneNew.b = 0.6980392;
		c4PegInTuneNew.r = 0.6980392; c4PegInTuneNew.g = 0.2196078; c4PegInTuneNew.b = 0;
		c5PegInTuneNew.r = 0.1843137; c5PegInTuneNew.g = 0.6980392; c5PegInTuneNew.b = 0;
		*(Color*)string0PegInTune = c0PegInTuneNew; *(Color*)string1PegInTune = c1PegInTuneNew;	*(Color*)string2PegInTune = c2PegInTuneNew;	*(Color*)string3PegInTune = c3PegInTuneNew;	*(Color*)string4PegInTune = c4PegInTuneNew;	*(Color*)string5PegInTune = c5PegInTuneNew;
		

		 //name="GuitarRegistrarTextIndicatorBlind" id="3186002004"
		//uintptr_t string0TextNew = GetStringColor(0, text); uintptr_t string1TextNew = GetStringColor(1, text); uintptr_t string2TextNew = GetStringColor(2, text); uintptr_t string3TextNew = GetStringColor(3, text); uintptr_t string4TextNew = GetStringColor(4, text); uintptr_t string5TextNew = GetStringColor(5, text);
		
		Color c0TextNew; Color c1TextNew; Color c2TextNew; Color c3TextNew; Color c4TextNew; Color c5TextNew;
		c0TextNew.r = 0.2470588; c0TextNew.g = 1; c0TextNew.b = 0.7843137;
		c1TextNew.r = 1; c1TextNew.g = 0.2509804; c1TextNew.b = 0.2509804;
		c2TextNew.r = 1; c2TextNew.g = 1; c2TextNew.b = 0.2509804;
		c3TextNew.r = 0.2509804; c3TextNew.g = 0.5019608; c3TextNew.b = 1;
		c4TextNew.r = 1; c4TextNew.g = 0.627451; c4TextNew.b = 0.2509804;
		c5TextNew.r = 0.2509804; c5TextNew.g = 1; c5TextNew.b = 0.2509804;
		*(Color*)string0Text = c0TextNew; *(Color*)string1TextNew = c1TextNew;	*(Color*)string2TextNew = c2TextNew;	*(Color*)string3TextNew = c3TextNew;	*(Color*)string4TextNew = c4TextNew;	*(Color*)string5TextNew = c5TextNew;
		

		
		//name="GuitarRegistrarForkParticlesBlind" id="3239612871"
		//uintptr_t string0Part = GetStringColor(0, Particles); uintptr_t string1Part = GetStringColor(1, Particles); uintptr_t string2Part = GetStringColor(2, Particles); uintptr_t string3Part = GetStringColor(3, Particles); uintptr_t string4Part = GetStringColor(4, Particles); uintptr_t string5Part = GetStringColor(5, Particles);

		Color c0PartNew; Color c1PartNew; Color c2PartNew; Color c3PartNew; Color c4PartNew; Color c5PartNew;
		c0PartNew.r = 0.2470588; c0PartNew.g = 1; c0PartNew.b = 0.7843137;
		c1PartNew.r = 1; c1PartNew.g = 0.2509804; c1PartNew.b = 0.2509804;
		c2PartNew.r = 1; c2PartNew.g = 1; c2PartNew.b = 0.2509804;
		c3PartNew.r = 0.2509804; c3PartNew.g = 0.5019608; c3PartNew.b = 1;
		c4PartNew.r = 1; c4PartNew.g = 0.627451; c4PartNew.b = 0.2509804;
		c5PartNew.r = 0.2509804; c5PartNew.g = 1; c5PartNew.b = 0.2509804;
		*(Color*)string0Part = c0PartNew; *(Color*)string1Part = c1PartNew;	*(Color*)string2Part = c2PartNew;	*(Color*)string3Part = c3PartNew;	*(Color*)string4Part = c4PartNew;	*(Color*)string5Part = c5PartNew;
		

		
		//name="NotewayBodyPartsBodyNormBlind" id="3629363565"

		//uintptr_t string0BodyNorm = GetStringColor(0, BodyNorm); uintptr_t string1BodyNorm = GetStringColor(1, BodyNorm); uintptr_t string2BodyNorm = GetStringColor(2, BodyNorm); uintptr_t string3BodyNorm = GetStringColor(3, BodyNorm); uintptr_t string4BodyNorm = GetStringColor(4, BodyNorm); uintptr_t string5BodyNorm = GetStringColor(5, BodyNorm);

		Color c0BodyNormNew; Color c1BodyNormNew; Color c2BodyNormNew; Color c3BodyNormNew; Color c4BodyNormNew; Color c5BodyNormNew;
		c0BodyNormNew.r = 0; c0BodyNormNew.g = 0.7764706; c0BodyNormNew.b = 0.5568628;
		c1BodyNormNew.r = 1; c1BodyNormNew.g = 0; c1BodyNormNew.b = 0;
		c2BodyNormNew.r = 1; c2BodyNormNew.g = 1; c2BodyNormNew.b = 0;
		c3BodyNormNew.r = 0; c3BodyNormNew.g = 0.1176471; c3BodyNormNew.b = 1;
		c4BodyNormNew.r = 1; c4BodyNormNew.g = 0.5450981; c4BodyNormNew.b = 0.1843137;
		c5BodyNormNew.r = 0; c5BodyNormNew.g = 1; c5BodyNormNew.b = 0.1764706;
		*(Color*)string0BodyNorm = c0BodyNormNew; *(Color*)string1BodyNorm = c1BodyNormNew;	*(Color*)string2BodyNorm = c2BodyNormNew;	*(Color*)string3BodyNorm = c3BodyNormNew;	*(Color*)string4BodyNorm = c4BodyNormNew;	*(Color*)string5BodyNorm = c5BodyNormNew;
		
		
		
		// = name = "NotewayBodyPartsAccentBlind" id = "47948252"
		//uintptr_t string0BodyAcc = GetStringColor(0, BodyAcc); uintptr_t string1BodyAcc = GetStringColor(1, BodyAcc); uintptr_t string2BodyAcc = GetStringColor(2, BodyAcc); uintptr_t string3BodyAcc = GetStringColor(3, BodyAcc); uintptr_t string4BodyAcc = GetStringColor(4, BodyAcc); uintptr_t string5BodyAcc = GetStringColor(5, BodyAcc);

		Color c0BodyAccNew; Color c1BodyAccNew; Color c2BodyAccNew; Color c3BodyAccNew; Color c4BodyAccNew; Color c5BodyAccNew;
		c0BodyAccNew.r = 1; c0BodyAccNew.g = 1; c0BodyAccNew.b = 1;
		c1BodyAccNew.r = 0.9764706; c1BodyAccNew.g = 0.572549; c1BodyAccNew.b = 0.5372549;
		c2BodyAccNew.r = 0.9843137; c2BodyAccNew.g = 0.9490196; c2BodyAccNew.b = 0.5843138;
		c3BodyAccNew.r = 0.5490196; c3BodyAccNew.g = 0.9098039; c3BodyAccNew.b = 0.9921569;
		c4BodyAccNew.r = 0.9882353; c4BodyAccNew.g = 0.8196079; c4BodyAccNew.b = 0.5254902;
		c5BodyAccNew.r = 0.6901961; c5BodyAccNew.g = 0.9568627; c5BodyAccNew.b = 0.5137255;
		*(Color*)string0BodyAcc = c0BodyAccNew; *(Color*)string1BodyAcc = c1BodyAccNew;	*(Color*)string2BodyAcc = c2BodyAccNew;	*(Color*)string3BodyAcc = c3BodyAccNew;	*(Color*)string4BodyAcc = c4BodyAccNew;	*(Color*)string5BodyAcc = c5BodyAccNew;
		

		
		//= name = "NotewayBodyPartsPreviewBlind" id = "338656387"
		//uintptr_t string0BodyPrev = GetStringColor(0, BodyPrev); uintptr_t string1BodyPrev = GetStringColor(1, BodyPrev); uintptr_t string2BodyPrev = GetStringColor(2, BodyPrev); uintptr_t string3BodyPrev = GetStringColor(3, BodyPrev); uintptr_t string4BodyPrev = GetStringColor(4, BodyPrev); uintptr_t string5BodyPrev = GetStringColor(5, BodyPrev);

		Color c0BodyPrevNew; Color c1BodyPrevNew; Color c2BodyPrevNew; Color c3BodyPrevNew; Color c4BodyPrevNew; Color c5BodyPrevNew;
		c0BodyPrevNew.r = 0.1607843; c0BodyPrevNew.g = 0.2470588; c0BodyPrevNew.b = 0.2235294;
		c1BodyPrevNew.r = 0.2509804; c1BodyPrevNew.g = 0.1607843; c1BodyPrevNew.b = 0.1607843;
		c2BodyPrevNew.r = 0.2509804; c2BodyPrevNew.g = 0.227451; c2BodyPrevNew.b = 0.1607843;
		c3BodyPrevNew.r = 0.1607843; c3BodyPrevNew.g = 0.2078431; c3BodyPrevNew.b = 0.2509804;
		c4BodyPrevNew.r = 0.2509804; c4BodyPrevNew.g = 0.2; c4BodyPrevNew.b = 0.1607843;
		c5BodyPrevNew.r = 0.1647059; c5BodyPrevNew.g = 0.2509804; c5BodyPrevNew.b = 0.1607843;
		*(Color*)string0BodyPrev = c0BodyPrevNew; *(Color*)string1BodyPrev = c1BodyPrevNew;	*(Color*)string2BodyPrev = c2BodyPrevNew;	*(Color*)string3BodyPrev = c3BodyPrevNew;	*(Color*)string4BodyPrev = c4BodyPrevNew;	*(Color*)string5BodyPrev = c5BodyPrevNew;
		
		// this comment block can be removed once the memory spaces are identified in structs.h - I think
		*/ 

		/* Color cNnew, cDnew, cHnew; // existing code. NFI what it did...
		cNnew = cN;
		cNnew.setH(5);
		cDnew = cD;
		cDnew.setH(5);
		cHnew = cH;
		cHnew.setH(5);

		*(Color*)string0n = cNnew;
		
		*(Color*)string0h = cHnew;
		
		*(Color*)string0d = cDnew;
		*/
		

		
		
	}
	else {
	
	}
}

void cERMode::ToggleRainbowMode() {
	RainbowEnabled = !RainbowEnabled;
}

void cERMode::DoRainbow() {
	if (!RainbowEnabled)
		return;

	std::vector<uintptr_t> stringsNormal;
	std::vector<uintptr_t> stringsHigh;
	std::vector<uintptr_t> stringsDisabled;
	std::vector<Color> oldNormal, oldHigh, oldDisabled;

	for (int i = 0; i < 6; i++) {
		stringsNormal.push_back(GetStringColor(i, normal));
		stringsHigh.push_back(GetStringColor(i, highlight));
		stringsDisabled.push_back(GetStringColor(i, disabled));
	}

	Color c;
	c.r = 1.f;
	c.g = 0.f;
	c.b = 0.f;

	float h = 0.f;
	float speed = 2.f;
	float stringOffset = 20.f;

	while (RainbowEnabled) {

		h += speed;
		if (h >= 360.f) { h = 0.f; }

		for (int i = 0; i < 6; i++) {
			oldNormal.push_back(*(Color*)stringsNormal[i]);
			oldHigh.push_back(*(Color*)stringsHigh[i]);
			oldDisabled.push_back(*(Color*)stringsDisabled[i]);

			c.setH(h + (stringOffset * i));

			*(Color*)stringsNormal[i] = c;
			*(Color*)stringsHigh[i] = c;
			*(Color*)stringsDisabled[i] = c;
		}

		Sleep(16);
	}

	if (oldNormal.size() == 0)
		return;

	for (int i = 0; i < 6; i++) {
		*(Color*)stringsNormal[i] = oldNormal[i];
		*(Color*)stringsHigh[i] = oldHigh[i];
		*(Color*)stringsDisabled[i] = oldDisabled[i];
	}
}
