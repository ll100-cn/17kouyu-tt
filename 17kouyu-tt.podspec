#
# Be sure to run `pod lib lint 17kouyu-tt.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = "17kouyu-tt"
  s.version          = "20200624"
  s.summary          = "声通 iOS 语音 SDK"
  s.description      = <<-DESC
    声通 iOS 语音 SDK
  DESC

  s.homepage         = "http://stkouyu.com/"
  s.license          = 'UNLICENSE'
  s.author           = { "17kouyu" => "stkouyu.com" }
  s.source           = { git: "https://github.com/ll100-cn/17kouyu-tt.git", tag: s.version }

  s.platform     = :ios, '9.0'
  s.requires_arc = true

  s.vendored_frameworks = 'ios/STKouyuEngine.framework'
  s.vendored_libraries = 'ios/libskegn.a', 'ios/libopus.a'
  s.resource = 'ios/STKouyuEngine.bundle'
  s.frameworks = %w(
    Foundation
    CoreGraphics
    Security
    SystemConfiguration
    CFNetwork
    Accelerate
    AudioToolbox
  )
  s.libraries = 'z.1'
end
