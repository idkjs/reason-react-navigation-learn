// open ReactNative;
// open ReactNavigation;

[@react.component]
let app = () => {
  // open PassingParamsDemo;
  open SettingHeaderStyles;
  let screenProps = {"someProp": 42};
  <AppContainer screenProps />;
};