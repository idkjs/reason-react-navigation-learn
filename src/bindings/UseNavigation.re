type t;

[@bs.val] [@bs.module "react-navigation"]
external navigationContext: React.Context.t(t) = "NavigationContext";

let useNavigation = () => React.useContext(navigationContext);