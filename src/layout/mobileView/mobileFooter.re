[%bs.raw {|require('./mobileFooter.css')|}];

let component = ReasonReact.statelessComponent("MobileFooter");

open SocialData;

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="mobile-footer">
      <hr />
      <div className="footer-links__wrapper">
        <FooterLink link=githubLink />
        <FooterLink link=stackOverflowLink />
        <FooterLink link=linkedInLink />
      </div>
    </div>
};
