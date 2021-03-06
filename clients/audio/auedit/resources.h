/*
 * generated by appdef from Auedit.ad
 */

/*  $NCDId: @(#)resources.h,v 1.6 1994/11/01 23:19:25 greg Exp $ */
"*input:                          true",
"*auedit.translations:            #override\\n\
	<Message>WM_PROTOCOLS: quit()",
"*auedit.TransientShell.translations: #override\\n\
	<Message>WM_PROTOCOLS: quit()",
"*font:                           *courier-medium-r-normal*140*",
"*Text.translations:              #override\\n\
	<Key>Return: beginning-of-line()",
"*fileMenuButton.label:           File",
"*fileMenuButton.menuName:        fileMenu",
"*fileNew.label:                  New...",
"*fileLoad.label:                 Load...",
"*fileSave.label:                 Save",
"*fileSaveAs.label:               Save as...",
"*fileSaveInterval.label:         Save interval...",
"*fileRevert.label:               Revert",
"*fileExit.label:                 Exit",
"*editMenuButton.label:           Edit",
"*editMenuButton.menuName:        editMenu",
"*editMenuButton.fromHoriz:       fileMenuButton",
"*editCut.label:                  Cut",
"*editCopy.label:                 Copy",
"*editPasteInsert.label:          Paste insert",
"*editPasteReplace.label:         Paste replace",
"*editPasteMix.label:             Paste mix",
"*editUndo.label:                 Undo",
"*zoomMenuButton.label:           Zoom",
"*zoomMenuButton.menuName:        zoomMenu",
"*zoomMenuButton.fromHoriz:       editMenuButton",
"*zoomIn.label:                   In",
"*zoomOut.label:                  Out",
"*zoomMarkers.label:              Markers",
"*zoomFull.label:                 Full",
"*effectsMenuButton.label:        Effects",
"*effectsMenuButton.menuName:     effectsMenu",
"*effectsMenuButton.fromHoriz:    zoomMenuButton",
"*effectsAmplitude.label:         Amplitude...",
"*effectsMaxAmplitude.label:      Max Amplitude",
"*effectsReverse.label:           Reverse",
"*effectsFadeIn.label:            Fade In",
"*effectsFadeOut.label:           Fade Out",
"*record.label:                   Record",
"*record.fromHoriz:               effectsMenuButton",
"*filename.label:                 \\ ",
"*filename.fromHoriz:             record",
"*filename.borderWidth:           0",
"*filename.resizable:             true",
"*volumeSlider.fromVert:          fileMenuButton",
"*volumeSlider.label:             Volume:  %3d%%",
"*volumeSlider.min:               1",
"*volumeSlider.max:               200",
"*volumeSlider.value:             100",
"*volumeSlider.resizable:         true",
"*graph.width:                    500",
"*graph.height:                   100",
"*graph.fromVert:                 volumeSlider",
"*leftLabel.label:                Start",
"*leftLabel.fromVert:             graph",
"*leftLabel.borderWidth:          0",
"*leftTime.fromVert:              leftLabel",
"*leftTime.label:                 00:00.00",
"*durationLabel.label:            Duration",
"*durationLabel.fromHoriz:        leftTime",
"*durationLabel.fromVert:         graph",
"*durationLabel.borderWidth:      0",
"*durationTime.fromHoriz:         leftTime",
"*durationTime.fromVert:          durationLabel",
"*durationTime.label:             00:00.00",
"*rightLabel.label:               End",
"*rightLabel.fromHoriz:           durationTime",
"*rightLabel.fromVert:            graph",
"*rightLabel.borderWidth:         0",
"*rightTime.fromHoriz:            durationTime",
"*rightTime.fromVert:             rightLabel",
"*rightTime.label:                00:00.00",
"*positionLabel.label:            Position",
"*positionLabel.fromHoriz:        rightTime",
"*positionLabel.fromVert:         graph",
"*positionLabel.borderWidth:      0",
"*positionLabel.horizDistance:    20",
"*positionTime.fromHoriz:         rightTime",
"*positionTime.fromVert:          positionLabel",
"*positionTime.label:             00:00.00",
"*positionTime.horizDistance:     20",
"*play.fromHoriz:                 positionTime",
"*play.fromVert:                  positionLabel",
"*play.horizDistance:             40",
"*stop.fromVert:                  positionLabel",
"*stop.fromHoriz:                 play",
"*pause.fromVert:                 positionLabel",
"*pause.fromHoriz:                stop",
"*fileFormatLabel.label:          File format:",
"*fileFormatLabel.borderWidth:    0",
"*fileFormatLabel.fromVert:       leftTime",
"*fileFormatLabel.vertDistance:   30",
"*fileFormatMenuButton.fromHoriz: fileFormatLabel",
"*fileFormatMenuButton.fromVert:  leftTime",
"*fileFormatMenuButton.menuName:  fileFormatMenu",
"*fileFormatMenuButton.vertDistance: 30",
"*fileFormatMenuButton.resizable: true",
"*dataFormatLabel.label:          Data format:",
"*dataFormatLabel.borderWidth:    0",
"*dataFormatLabel.fromVert:       fileFormatMenuButton",
"*dataFormatMenuButton.fromHoriz: dataFormatLabel",
"*dataFormatMenuButton.fromVert:  fileFormatMenuButton",
"*dataFormatMenuButton.menuName:  dataFormatMenu",
"*dataFormatMenuButton.resizable: true",
"*frequencyLabel.label:           \\  Frequency:",
"*frequencyLabel.borderWidth:     0",
"*frequencyLabel.fromVert:        dataFormatMenuButton",
"*frequency.fromHoriz:            frequencyLabel",
"*frequency.fromVert:             dataFormatMenuButton",
"*frequency*editType:             edit",
"*frequency.translations:         #override\\n\
	<Key>Return: beginning-of-line()\\n\
	<LeaveNotify>: updateFrequency()",
"*commentLabel.label:             \\    Comment:",
"*commentLabel.borderWidth:       0",
"*commentLabel.fromVert:          frequency",
"*comment.fromVert:               commentLabel",
"*comment.resizable:              true",
"*comment*editType:               edit",
"*dialogShell.allowShellResize:   true",
"*dialog.label.resizable:         true",
"*dialog.value.translations:      #override\\n\
	<Key>Return: ok()",
"*dialog.okButton.label:          Ok",
"*dialog.cancelButton.label:      Cancel",
"*errorShell.allowShellResize:    true",
"*error.label.resizable:          true",
"*error.okButton.label:           Acknowledge",
"*warningShell.allowShellResize:  true",
"*warning.label.resizable:        true",
"*warning.okButton.label:         Yes",
"*warning.cancelButton.label:     No",
"*recordShell.title:              Record",
"*recordDurationLabel.label:      \\  Duration:",
"*recordDurationLabel.borderWidth: 0",
"*duration.fromHoriz:             recordDurationLabel",
"*duration*editType:              edit",
"*duration.translations:          #override\\n\
	<Key>Return: beginning-of-line()",
"*duration*string:                10",
"*recordFreqLabel.label:          \\ Frequency:",
"*recordFreqLabel.borderWidth:    0",
"*recordFreqLabel.fromVert:       recordDurationLabel",
"*recordFreq.fromHoriz:           recordFreqLabel",
"*recordFreq.fromVert:            recordDurationLabel",
"*recordFreq*editType:            edit",
"*recordFreq.translations:        #override\\n\
	<Key>Return: beginning-of-line()",
"*recordFreq*string:              8000",
"*modeLabel.label:                Input Mode:",
"*modeLabel.borderWidth:          0",
"*modeLabel.fromVert:             recordFreqLabel",
"*mode.fromHoriz:                 modeLabel",
"*mode.fromVert:                  recordFreqLabel",
"*gainSlider.fromVert:            modeLabel",
"*gainSlider.label:               Gain:  %3d%%",
"*gainSlider.min:                 1",
"*gainSlider.max:                 100",
"*gainSlider.resizable:           true",
"*recordStart.label:              Record",
"*recordStart.fromVert:           gainSlider",
"*monitor.label:                  Monitor",
"*monitor.fromVert:               gainSlider",
"*monitor.fromHoriz:              recordStart",
"*dismiss.label:                  Dismiss",
"*dismiss.fromVert:               gainSlider",
"*dismiss.fromHoriz:              monitor",
