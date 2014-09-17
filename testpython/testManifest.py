import file_operate
import modifyManifest

file_operate.setPrintEnable(1)
modifyManifest.modifyApplicationActivity('configChanges', "orientation|screenSize|keyboardHidden")
# modifyManifest.renameAppName("@string/app_name")